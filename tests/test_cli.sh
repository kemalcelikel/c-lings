#!/bin/sh
# Exercise the real native CLI and Make workflow in a disposable course copy.
set -eu
root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
compiler=$(command -v "${1:-gcc}")
temp=$(mktemp -d)
pid=
cleanup() {
    if [ -n "$pid" ]; then kill -TERM "$pid" 2>/dev/null || :; wait "$pid" 2>/dev/null || :; fi
    rm -rf -- "$temp"
}
trap cleanup EXIT HUP INT TERM
fixture="$temp/course with spaces"
mkdir -p "$fixture/exercises" "$fixture/solutions" "$fixture/tools" "$temp/work"
cp "$root/clings" "$root/Makefile" "$fixture/"
cp -R "$root/src" "$fixture/"
cp "$root"/exercises/*.c "$fixture/exercises/"
cp "$root"/solutions/*.patch "$fixture/solutions/"
cp "$root/tools/make_patch.sh" "$fixture/tools/"
export TMPDIR="$temp/work"
log="$temp/log"
count=0

run() {
    expected=$1; shift
    status=0
    "$@" > "$log" 2>&1 || status=$?
    if [ "$status" -ne "$expected" ]; then
        cat "$log" >&2
        printf 'Expected exit %s, got %s: %s\n' "$expected" "$status" "$*" >&2
        exit 1
    fi
}
contains() { grep -Fq -- "$1" "$log" || { cat "$log" >&2; exit 1; }; }
lacks() { if grep -Fq -- "$1" "$log"; then cat "$log" >&2; exit 1; fi; }
passed() { count=$((count + 1)); printf 'PASS %s\n' "$1"; }
source_file() {
    printf '#include <stdio.h>\nint main(void) { %s }\n// CHECK-EXACT: hello\n' "$2" > "$fixture/exercises/$1"
}

run 1 "$fixture/clings"
contains '001_hello.c'
[ ! -e "$fixture/.clings-progress" ]
passed 'fresh course starts at intended first failure'

run 0 "$fixture/clings" --list
contains '032b_double_pointers.c'
[ "$(wc -l < "$log")" -eq 97 ]
run 0 "$fixture/clings" --list --start 039
contains '039_files_read.c'
lacks '038_realloc.c'
passed 'listing, suffix identifiers, and explicit start selection'

run 0 "$fixture/clings" --exercise 999
contains 'You are now a C programmer!'
[ ! -e "$fixture/.clings-progress" ]
passed 'external directory invocation and single lesson do not record progress'

for id in 063 nonsense 032bb; do run 2 "$fixture/clings" --exercise "$id"; contains 'Unknown exercise'; done
run 2 "$fixture/clings" --exercise 001 --start 002
run 2 "$fixture/clings" --verify --random
run 2 "$fixture/clings" --timeout
run 2 "$fixture/clings" --unknown
for value in 0 -1 nan inf 5seconds; do run 2 "$fixture/clings" --timeout "$value"; done
passed 'invalid selections, conflicting options, and timeouts fail'

source_file 001_hello.c 'puts("hello"); return 0;'
source_file 002_variables.c 'return 7;'
run 1 "$fixture/clings"
contains '002_variables.c'
lacks 'Checking 003_arrays.c'
[ "$(cat "$fixture/.clings-progress")" = 001 ]
run 1 "$fixture/clings"
lacks 'Checking 001_hello.c'
contains '002_variables.c'
[ "$(cat "$fixture/.clings-progress")" = 001 ]
passed 'normal mode saves only successful progress and resumes at failure'

source_file 002_variables.c 'puts("hello"); return 0;'
source_file 003_arrays.c 'return 7;'
run 2 make -C "$fixture" CC="$compiler"
contains 'Checking 003_arrays.c'
[ "$(cat "$fixture/.clings-progress")" = 002 ]
run 2 make -C "$fixture" CC="$compiler"
lacks 'Checking 002_variables.c'
passed 'default Make invokes checker even when executable is up to date'

source_file 032_pointers_modify.c 'puts("hello"); return 0;'
source_file 032b_double_pointers.c 'puts("hello"); return 0;'
source_file 032c_const_pointers.c 'return 7;'
printf '031\n' > "$fixture/.clings-progress"
run 1 "$fixture/clings"
contains 'Checking 032_pointers_modify.c'
contains 'Checking 032b_double_pointers.c'
contains 'Checking 032c_const_pointers.c'
[ "$(cat "$fixture/.clings-progress")" = 032b ]
run 1 "$fixture/clings"
lacks 'Checking 032b_double_pointers.c'
passed 'saved progress represents suffixed lessons correctly'

run 0 "$fixture/clings" --exercise 000001
run 1 "$fixture/clings" --start 003
run 1 "$fixture/clings" --all
[ "$(cat "$fixture/.clings-progress")" = 032b ]
status=0
"$fixture/clings" --random > "$log" 2>&1 || status=$?
[ "$status" -le 1 ]
[ "$(grep -c 'Checking ' "$log")" -eq 1 ]
[ "$(cat "$fixture/.clings-progress")" = 032b ]
passed 'single, start, all, and random modes preserve normal progress'

printf 'invalid\n' > "$fixture/.clings-progress"
run 2 "$fixture/clings"
contains 'Invalid saved progress'
run 0 "$fixture/clings" --list
run 0 make -C "$fixture" reset CC="$compiler"
[ ! -e "$fixture/.clings-progress" ]
grep -Fq 'puts("hello")' "$fixture/exercises/001_hello.c"
run 0 "$fixture/clings" --reset
passed 'invalid state fails; reset is idempotent and preserves exercise edits'

printf '094\n' > "$fixture/.clings-progress"
run 0 "$fixture/clings"
contains '999_the_end.c'
[ "$(cat "$fixture/.clings-progress")" = 999 ]
run 0 "$fixture/clings"
contains 'All C exercises completed'
lacks 'Checking '
passed 'conclusion records completion and completed runs skip compilation'

run 0 make -C "$fixture" clean
[ ! -e "$fixture/clings" ]
[ "$(cat "$fixture/.clings-progress")" = 999 ]
run 0 make -C "$fixture" build CC="$compiler"
run 0 make -C "$fixture" list CC="$compiler"
contains '032b_double_pointers.c'
run 0 make -C "$fixture" n=001 CC="$compiler"
run 2 make -C "$fixture" s=003 CC="$compiler"
passed 'Make bootstraps native runner, honors n/s, and clean preserves progress'

export CLINGS_TEST_CC="$compiler" CLINGS_COMPILER_LOG="$temp/compiler-log"
wrapper="$temp/compiler wrapper"
printf '#!/bin/sh\nprintf "used\\n" >> "$CLINGS_COMPILER_LOG"\nexec "$CLINGS_TEST_CC" "$@"\n' > "$wrapper"
chmod +x "$wrapper"
run 0 make -C "$fixture" n=001 CC="$wrapper"
[ -s "$CLINGS_COMPILER_LOG" ]
run 2 "$fixture/clings" --exercise 001 --cc clings-missing-compiler
contains 'cannot execute'
passed 'compiler override reaches the exercise compiler, including paths with spaces'

# Restore the audited course before checking patch coverage and application.
cp "$root"/exercises/*.c "$fixture/exercises/"
run 0 "$fixture/clings" --verify --exercise 001
contains 'Verified 1 lessons; 0 failed.'
[ "$(cat "$fixture/.clings-progress")" = 999 ]
passed 'verification ignores completed learner progress'

mv "$fixture/solutions/001_hello.patch" "$temp/answer.patch"
run 2 "$fixture/clings" --verify
contains 'missing patch'
cp "$temp/answer.patch" "$fixture/solutions/extra.patch"
run 2 "$fixture/clings" --verify
contains 'extra patch'
rm "$fixture/solutions/extra.patch"
cp "$temp/answer.patch" "$fixture/solutions/001_hello.patch"
printf 'not a patch\n' > "$fixture/solutions/001_hello.patch"
run 1 "$fixture/clings" --verify
contains 'PATCH ERROR'
cp "$temp/answer.patch" "$fixture/solutions/001_hello.patch"
passed 'missing, extra, and malformed solution patches fail'

mv "$fixture/exercises/001_hello.c" "$temp/lesson.c"
run 2 "$fixture/clings" --list
contains 'missing exercise'
cp "$temp/lesson.c" "$fixture/exercises/001_duplicate.c"
run 2 "$fixture/clings" --list
contains 'extra or renamed exercise'
rm "$fixture/exercises/001_duplicate.c"
mv "$temp/lesson.c" "$fixture/exercises/001_hello.c"
passed 'empty or partial discovery and duplicate lessons cannot silently pass'

awk '/001_hello.c/ { first = $0; next } /002_variables.c/ { print; print first; next } { print }' \
    "$fixture/src/course.h" > "$temp/course.h"
cp "$temp/course.h" "$fixture/src/course.h"
run 0 make -C "$fixture" build CC="$compiler"
run 2 "$fixture/clings" --list
contains 'not in numeric/suffix order'
cp "$root/src/course.h" "$fixture/src/course.h"
run 0 make -C "$fixture" build CC="$compiler"
passed 'out-of-order compiled registry is rejected'

answers="$temp/answers with spaces"
mkdir "$answers"
patch --batch --fuzz=0 -o "$answers/001_hello.c" "$fixture/exercises/001_hello.c" "$temp/answer.patch" > "$log"
run 0 sh "$fixture/tools/make_patch.sh" "$answers/001_hello.c"
cmp "$fixture/solutions/001_hello.patch" "$temp/answer.patch"
run 0 "$fixture/clings" --verify --exercise 001
cp "$answers/001_hello.c" "$fixture/exercises/001_hello.c"
run 2 sh "$fixture/tools/make_patch.sh" "$answers/001_hello.c"
contains 'identical'
cp "$root/exercises/001_hello.c" "$fixture/exercises/001_hello.c"
printf 'broken C\n' > "$answers/001_hello.c"
run 1 sh "$fixture/tools/make_patch.sh" "$answers/001_hello.c"
cmp "$fixture/solutions/001_hello.patch" "$temp/answer.patch"
passed 'native patch generation validates answers, handles diff exit codes, and preserves patches on failure'

printf '#include <stdio.h>\nint main(void) { FILE *f = fopen("%s/ready", "w"); if (!f) return 1; fclose(f); for (;;) {} }\n// CHECK: done\n' "$temp" > "$answers/001_hello.c"
"$fixture/clings" --check-file "$answers/001_hello.c" > "$log" 2>&1 &
pid=$!
tries=0
while [ ! -e "$temp/ready" ] && [ "$tries" -lt 100 ]; do sleep 0.02; tries=$((tries + 1)); done
[ -e "$temp/ready" ]
kill -INT "$pid"
status=0
wait "$pid" || status=$?
pid=
[ "$status" -eq 130 ]
contains 'Interrupted'
[ -z "$(ls -A "$temp/work")" ]
passed 'Ctrl+C stops the running program and removes all temporary data'

printf '%s CLI/Make workflow tests passed.\n' "$count"

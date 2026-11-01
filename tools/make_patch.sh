#!/bin/sh
# Generate a patch only after the native checker validates the solved copy.
set -eu

if [ "$#" -ne 1 ]; then
    printf 'Usage: sh tools/make_patch.sh /path/to/answers/001_hello.c\n' >&2
    exit 2
fi
root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
answer=$(realpath -- "$1")
name=$(basename -- "$answer")
original="$root/exercises/$name"
if [ ! -f "$original" ]; then
    printf 'Answer must use an original course filename.\n' >&2
    exit 2
fi
make -C "$root" build
"$root/clings" --check-file "$answer"
destination="$root/solutions/${name%.c}.patch"
temp=$(mktemp "$root/solutions/.patch-XXXXXX")
trap 'rm -f -- "$temp"' EXIT HUP INT TERM
status=0
diff -u --label "$name" --label "$name" -- "$original" "$answer" > "$temp" || status=$?
case "$status" in
    0) printf 'Answer is identical to the learner source.\n' >&2; exit 2 ;;
    1) mv -- "$temp" "$destination" ;;
    *) printf 'Could not generate solution patch.\n' >&2; exit "$status" ;;
esac
printf '%s\n' "$destination"

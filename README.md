# Clings

Learn C by fixing small, intentionally broken programs.

Clings contains **96 exercises and a conclusion**. Read each lesson's comments,
fix its mistakes, and let the compiler and checker guide you. The course covers
the basics, pointers, allocation, the standard library, and selected systems
topics. The runner itself is written in C and built with GCC and GNU Make.

Inspired by [Ziglings](https://codeberg.org/ziglings/exercises) and
[Rustlings](https://github.com/rust-lang/rustlings). No other language runtime
is needed to learn, test, or maintain Clings.

## Getting started

The supported baseline is **Linux, GCC 11+, and GNU Make**. Windows users can
use WSL. Native Windows and macOS have not been verified for the whole course.
Some advanced lessons use clearly identified POSIX APIs or GCC extensions.

On Debian or Ubuntu:

```sh
sudo apt update
sudo apt install build-essential
git clone https://github.com/kemalcelikel/c-lings.git clings
cd clings
make
```

`make` automatically builds the native checker, then checks lessons in order.
It should stop at `exercises/001_hello.c`: the missing `<stdio.h>` include is
your first task.

1. Read the diagnostics and the exercise's comments.
2. Edit the `.c` file in `exercises/`.
3. Run **`make` again**.

The checker saves progress after each successful lesson and resumes at the next
unfinished lesson. It stops at the first compiler, runtime, or output failure.
Earlier completed lessons are not rechecked by default; use `make all` to recheck
everything. There is no automatic watch mode.

## Useful commands

```sh
make n=032b       # Check one lesson
make s=039        # Check from a chosen lesson
make random      # Check one randomly selected lesson
make list        # List the course
make all         # Recheck everything without changing progress
make reset       # Reset progress, preserving your exercise edits
make build       # Build the checker without running lessons
make clean       # Remove native build artifacts, preserving progress and edits
```

Identifiers accept leading zeros. Base lessons precede suffixes: 032, 032b,
032c, 033, 033b. There is no 063; 999 is the conclusion.

Only normal `make` / `./clings` runs update `.clings-progress`. Single-lesson,
explicit-start, random, list, full-check, and verification modes do not alter it.
This prevents checking a later lesson from skipping earlier unfinished work.

The executable also supports direct invocation, including from another directory:

```sh
./clings --help
./clings --exercise 051 --timeout 10
/path/to/clings/clings --exercise 032b
make CC=gcc-12
```

Make passes `CC` to both native builds and exercise compilation. Direct
invocations accept `--cc` or the `CC` environment variable; it must identify a
single compiler executable. GCC is the verified baseline.

## How checking works

Exercises compile with:

```sh
gcc -std=c11 -Wall -Wextra -Werror -pedantic FILE.c -o ./FILE.out -pthread -lm
```

These flags select C11, enable common warnings and treat them as errors, and
link POSIX threads and math functions. Explicitly taught GCC attributes remain
accepted extensions; `-pedantic` does not disable every extension.

Each lesson runs in an isolated temporary copy of the course, with no extra
arguments and its inherited environment. File-reading lessons can access the
course sources. Executables and lesson-created data are cleaned up after
success, failure, timeout, or interruption. Compilation has a limit of at least
30 seconds; runtime defaults to 5 seconds. Captured stdout is limited to 1 MiB.

Source comments specify expected stdout:

- `// CHECK:` requires substrings in order.
- `// CHECK-EXACT:` lines describe the complete output, ignoring outer whitespace.
- `// CHECK-ANY:` requires substrings in any order, for nondeterministic output.

Stderr diagnostics are displayed directly and are not compared to stdout checks.
Line endings are normalized for checking, including CRLF source comments.
Missing expectations, wrong output, failed compilation, nonzero exit, or timeout
cause a failing checker status. The native runner uses POSIX process/filesystem
APIs and Linux `/proc/self/exe` to locate the project relative to its executable.

## Course and maintenance

See [COURSE.md](COURSE.md) for the inventory and platform notes, and
[CONTRIBUTING.md](CONTRIBUTING.md) for lesson and patch maintenance.

Maintainers verify solved temporary copies, not the intentionally broken course:

```sh
sudo apt install patch diffutils
make test
make verify
make verify-sanitize
```

Verification requires one solution patch per learner exercise, checks that all
97 solved files pass and all 96 starters retain tasks, and ignores saved progress.
GitHub Actions runs native tests and course/sanitizer checks on Ubuntu 22.04/24.04.
It also checks the native runner itself with address/undefined-behavior sanitizers.

## Credits and license

Clings is derived from Ziglings, initiated by Dave Gauer and maintained with
Chris Boesch and other contributors. Thanks to Ziglings and Rustlings for the
learn-by-fixing approach. Distributed under the [MIT license](LICENSE), with
upstream copyright notices preserved.

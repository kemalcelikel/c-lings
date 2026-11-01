# Contributing to Clings

Clings teaches C through small, intentionally broken programs. Improve lesson
explanations and incidental bugs while preserving their intended learner tasks.

## Repository layout

- `exercises/`: 96 learner C exercises and a complete conclusion.
- `src/clings.c`: native CLI, progress, selection, and verification mode.
- `src/runner.c` / `src/runner.h`: shared process, isolation, and output checking.
- `src/course.h`: explicit ordered course registry.
- `Makefile`: native build and learner/maintainer entry points.
- `solutions/`: minimal C solution patches.
- `tools/make_patch.sh`: native-validated unified patch generation.
- `tests/test_runner.c`, `tests/test_cli.sh`: native and CLI/Make regression tests.
- `COURSE.md`: inventory and platform assumptions.

## Lesson changes

- Teach focused concepts using C terminology, with enough explanation in the
  comments and earlier lessons to solve the task.
- Keep C11 and the strict checker flags. Label POSIX APIs and GCC extensions.
- Correct solutions must avoid undefined behavior, invalid lifetimes, leaks,
  unchecked failed allocations, and uninitialized reads.
- Keep source comments, output expectations, and solution patches aligned. Use
  exact checks where substrings could accept a wrong result; use unordered checks
  only for genuinely nondeterministic output.
- Make environment/file needs explicit. A lesson receives a temporary copy of
  course C sources, not another lesson's generated data.
- Preserve existing filenames/identifiers. When deliberately changing the course
  inventory, update `src/course.h`, `COURSE.md`, and the README count together.

## Solution patches and verification

`solutions/` contains maintainer answers; learners work in `exercises/`. Each
intentionally broken lesson needs a minimal solution patch. The complete
conclusion needs no patch.

Maintainer commands require GCC, GNU Make, and the standard `patch` and `diff`
utilities. Verification applies patches to temporary copies, checks exact course
and patch coverage, runs every solved lesson, and confirms that starters retain
their intended tasks. Missing, extra, malformed, or non-applicable patches fail
verification. Saved learner progress is neither read nor updated.

Create a solved copy outside learner sources, with its original filename. Include
any course source files it reads in the answers directory. Then run:

```sh
sh tools/make_patch.sh /path/to/answers/039_files_read.c
make verify n=039
make verify
make verify-sanitize
```

The script builds the native checker, validates the solved copy, and generates a
minimal patch with `diff`. An invalid or identical answer fails without replacing
the existing patch. Use `CC=gcc-12 sh tools/make_patch.sh PATH` to select a compiler.
Only broken learner sources and their patches belong in commits, not solved
working copies or generated files.

Commit each lesson fix or addition separately after verification. Include its
patch and directly required registry/inventory/count/test updates; keep unrelated
lesson edits and shared checker changes in separate commits. Preserve local
learner answers. When those answers are already solved, run maintenance checks
against a clean committed/staged snapshot containing the intended change rather
than resetting learner files.

## Runner and tooling changes

```sh
make test
make verify
make verify-sanitize
```

The native tests cover output checking, execution, timeouts, process-group cleanup,
symlink-safe temporary cleanup, and sanitizer failure. CLI tests exercise the
actual executable and Make entry points in a disposable copy, including saved
progress, suffixes, reset/completion, compiler overrides, patch coverage, and Ctrl+C.

Add focused regression cases for changed behavior. Follow the surrounding C and
shell style; no external test framework or language runtime is required. The
runner is C11 using POSIX APIs on Linux, with `/proc/self/exe` for root discovery.
Maintain compiler and runtime failure status distinctions; infrastructure errors
must not count as intentional starter failures.

Native build flags can be overridden through `CFLAGS`/`CPPFLAGS`. Run `make clean`
before checking a changed compiler or build-flag configuration, since Make tracks
source timestamps rather than compiler-option changes. Verification enables
fatal address/undefined-behavior sanitizers on solved exercises and never uses
or modifies learner progress.

A normal `make` failing at lesson 001 is expected and is not full-course proof.
`make reset` only clears progress; it never restores learner source files.

## Reporting issues and licensing

Include the lesson identifier, exact command, platform, compiler/Make versions,
and diagnostics. For unclear explanations, point to the missing concept or
contradictory comment. Retain upstream attribution and contribute under the MIT
license.

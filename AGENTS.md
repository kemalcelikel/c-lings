# Clings — Repository Guide

## Project identity

Clings is a C-only learning project inspired by Ziglings and Rustlings. Learners
fix small, intentionally broken C programs, read compiler diagnostics, and
rerun a checker. Explain concepts using C terminology and idioms; no Zig
knowledge or installation is required. Retain upstream license attribution.

## Repository map

- `exercises/`: 96 intentionally broken C exercises plus `999_the_end.c`, a
  complete conclusion. Preserve filenames and existing identifiers.
- `Makefile`: native builds and learner/maintainer entry points.
- `src/clings.c`: C learner CLI, progress, lesson selection, and verification.
- `src/runner.c` / `src/runner.h`: shared compiler/runtime/output checking.
- `src/course.h`: explicit ordered course registry.
- `solutions/`: minimal C solution patches; not learner working copies.
- `tools/make_patch.sh`: validates a solved copy and writes its solution patch.
- `tests/test_runner.c`, `tests/test_cli.sh`: native and CLI/Make regression tests.
- `.github/workflows/ci.yml`: Ubuntu 22.04/24.04 GCC and sanitizer verification.
- `README.md`, `CONTRIBUTING.md`, `COURSE.md`: setup, maintenance, and inventory.
- `PLAN.md`, `NATIVE_WORKFLOW.md`: conversion status and native workflow design.

## Learner workflow

The baseline is Linux (including WSL), GNU Make, and GCC 11+ with C11 support,
POSIX threads, and math libraries. Native Windows/macOS are not verified for the
whole course. Label POSIX APIs and GCC extensions explicitly; they are not ISO C.

From the repository root:

```sh
make
make n=032b
make s=039
make list
```

Make builds the C checker as `./clings`. It locates `exercises/` relative to its
executable using Linux `/proc/self/exe`, so an absolute executable path works
from another directory. Ordering is numeric, base lesson before suffixes:
032, 032b, 032c, 033, 033b. There is no 063. Invalid selections and empty discovery
fail with a nonzero exit status.

For each selected lesson it:

1. Copies the course's C files into an isolated temporary directory.
2. Compiles with `gcc -std=c11 -Wall -Wextra -Werror -pedantic FILE.c -o ./FILE.out -pthread -lm`.
3. Runs `./FILE.out` there, without extra arguments and with inherited environment.
4. Displays diagnostics and checks stdout against the source comments.
5. Cleans the temporary directory, including lesson-created files, on exit.

`// CHECK:` values are ordered substrings. `// CHECK-EXACT:` lines specify the
complete stdout ignoring outer whitespace. `// CHECK-ANY:` values are unordered
substrings for nondeterministic output. Missing expectations fail. Stderr is
displayed but is not matched against stdout checks.

Compilation timeout is at least 30 seconds; runtime defaults to 5 seconds and
can be changed with `--timeout`. `--cc` or CC selects a compiler executable;
Make passes its compiler choice to exercise checking as well as native builds.
Captured stdout is limited to 1 MiB. The native runner uses POSIX APIs.

Normal `make` / `./clings` runs save the last passed identifier (including its
suffix) in `.clings-progress` and resume at the next lesson. Failures do not
advance progress. Single-lesson, explicit-start, random, list, full-check, and
verification modes do not update it. `make all` rechecks from the beginning;
`make reset` removes progress, preserving learner edits. Invalid saved state
fails explicitly. There is no watch mode.

## Maintenance and verification

- Preserve intentional errors and placeholders unless asked to solve a lesson.
  Fix incidental defects without leaving solved learner sources.
- Keep lessons self-contained and aligned with earlier explanations, their
  solution patches, and their output expectations. Avoid undefined behavior,
  incorrect ownership, nondeterministic assertions, and host-specific wording.
- Follow the existing C and shell style; no additional runtime, third-party test
  framework, or separate formatter is required.
- Update a changed exercise's patch using a temporary solved copy with its
  original filename: `sh tools/make_patch.sh /path/to/answers/001_hello.c`.
  File-reading lessons also need their referenced sources in the answers folder.
- Verify changes with the commands below. Generated executables, data, and
  solved working copies must stay out of learner sources and commits.
- Commit each lesson fix or addition separately after verification, including
  its patch and only directly required registry/documentation/test updates.
  Shared checker changes belong in separate commits. Never stage unrelated
  learner answers. If learner files are locally solved, verify maintenance
  changes in a clean committed/staged snapshot without resetting those edits.

```sh
make test
make verify
make verify-sanitize
```

Native verification requires the standard `patch` utility, checks the explicit
`src/course.h` registry and patch coverage, rejects invalid patches, verifies every
solved lesson, and confirms starters retain a failing task. The conclusion needs
no patch. A normal learner run failing at 001's missing `<stdio.h>` is expected
and is not a full-course regression test.

When deliberately adding/removing lessons, update `src/course.h`, `COURSE.md`,
and README counts. For checker changes, test discovery/order, selection,
compiler/runtime failures, output mismatches, timeouts, successful progression,
progress/resume/reset, compiler overrides, and cleanup as relevant. Verification
must ignore saved progress and leave learner files unchanged. Sanitizers make
detected errors fatal; they supplement
ordinary C11 verification and are not required in the learner workflow.

---

## 1. Think Before Coding

**Don't assume. Don't hide confusion. Surface tradeoffs.**

Before implementing:

- State your assumptions explicitly. If uncertain, ask.
- If multiple interpretations exist, present them - don't pick silently.
- If a simpler approach exists, say so. Push back when warranted.
- If something is unclear, stop. Name what's confusing. Ask.

## 2. Simplicity First

**Minimum code that solves the problem. Nothing speculative.**

- No features beyond what was asked.
- No abstractions for single-use code.
- No "flexibility" or "configurability" that wasn't requested.
- No error handling for impossible scenarios.
- If you write 200 lines and it could be 50, rewrite it.

Ask yourself: "Would a senior engineer say this is overcomplicated?" If yes, simplify.

## 3. Surgical Changes

**Touch only what you must. Clean up only your own mess.**

When editing existing code:

- Don't "improve" adjacent code, comments, or formatting.
- Don't refactor things that aren't broken.
- Match existing style, even if you'd do it differently.
- If you notice unrelated dead code, mention it - don't delete it.

When your changes create orphans:

- Remove imports/variables/functions that YOUR changes made unused.
- Don't remove pre-existing dead code unless asked.

The test: Every changed line should trace directly to the user's request.

## 4. Goal-Driven Execution

**Define success criteria. Loop until verified.**

Transform tasks into verifiable goals:

- "Add validation" → "Write tests for invalid inputs, then make them pass"
- "Fix the bug" → "Write a test that reproduces it, then make it pass"
- "Refactor X" → "Ensure tests pass before and after"

For multi-step tasks, state a brief plan:

```
1. [Step] → verify: [check]
2. [Step] → verify: [check]
3. [Step] → verify: [check]
```

Strong success criteria let you loop independently. Weak criteria ("make it work") require constant clarification.

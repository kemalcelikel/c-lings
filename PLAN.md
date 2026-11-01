# Clings conversion plan and status

## Goal

A C-only learn-by-fixing course with the Ziglings-style build/check/resume loop,
implemented with GCC, GNU Make, a native C checker, and standard shell utilities.
Learner and maintainer workflows require no additional language runtime.

## Implemented

- The audited course contains 96 intentionally broken C lessons and a complete
  conclusion in `exercises/`, with 96 minimal patches in `solutions/`.
- Inherited language-specific exercises, build tools, branding, and CI were
  replaced while preserving upstream MIT attribution.
- `make` builds the native checker and resumes the course. Single-lesson,
  explicit-start, random, list, reset, and full-check modes are available.
- Normal runs atomically save the last successful identifier, including suffixes,
  in `.clings-progress`. Failure never advances state. Selection and verification
  modes do not change normal progress; reset preserves exercise edits.
- Shared native checking uses strict C11 compilation, isolated source copies,
  bounded execution/output capture, process-group termination, and cleanup on
  success, failure, timeout, and interruption.
- `make verify` validates registry/patch coverage, applies patches to temporary
  sources, and checks solved lessons plus intentional starter failures. It ignores
  learner progress. `make verify-sanitize` makes sanitizer errors fatal.
- `tools/make_patch.sh` validates solved copies through the native engine before
  generating unified patches with `diff`.
- Native C and shell CLI/Make regression tests replace the earlier test suite.
- Documentation and GitHub Actions now use Make commands exclusively.

## Implementation sequence

1. Audit the C course and establish working solutions — completed.
2. Implement the native checker, explicit registry, and Make bootstrap — completed.
3. Implement saved progress, selection, reset, and completion — completed.
4. Replace verification and patch generation — completed.
5. Port regression tests and check actual CLI/Make behavior — completed.
6. Replace documentation, metadata, and CI — completed.
7. Verify GCC baseline/newer compiler, sanitizers, and disposable-copy workflows —
   completed.

## Completed local verification

- 19 native runner test groups and 18 CLI/Make workflow test groups pass.
- All 97 solved lessons pass with GCC 11 and GCC 12; all 96 starters retain tasks.
- All 97 solved lessons pass address/undefined-behavior sanitizer verification.
- The native runner and tests also pass when themselves built with fatal address
  and undefined-behavior sanitizers.
- A disposable copy builds, progresses through the learner loop, runs tests,
  verifies the course, and generates patches with a restricted PATH containing
  no Python executable. Verification ignores completed progress and works with
  USER/USERNAME absent. Hash checks confirm learner sources remain unchanged.

## Verification criteria

- All 97 solved lessons pass, and all 96 starters retain a failing task.
- Course ordering and selection correctly handle 032, 032b, 032c, 033, and 033b.
- Saved progress resumes at failure, records completion, and never causes full
  verification to skip lessons.
- Native tests cover output checks, compiler/runtime failures, timeouts, bounded
  capture, process-group termination, symlink-safe cleanup, and sanitizer failure.
- CLI tests verify actual Make bootstrap, repeat invocation, external directories,
  paths with spaces, progress/reset, compiler overrides, patch generation/coverage,
  and Ctrl+C in a disposable course copy.
- A complete build/test/course verification uses no removed tooling and leaves
  learner sources unchanged, without lesson-created data or executables.

GitHub Actions is configured for Ubuntu 22.04 and 24.04. Hosted results are
established only when the changes are pushed and the workflow runs. Current
operating instructions are in README.md, CONTRIBUTING.md, and COURSE.md; the
detailed native design is recorded in NATIVE_WORKFLOW.md.

# Native Clings workflow review

## Implemented design

The tooling is **a C runner built by GNU Make**, plus standard Unix utilities
for patch creation. The learner uses `make` repeatedly, just as
the inherited Ziglings course uses `zig build`. Make builds the runner when
needed; the runner compiles exercises with GCC and manages course progression.

The native runner, Make entry points, saved progress, verification, patch
generation, and native/shell tests are implemented. The C exercise audit and
96 solution patches remain the baseline for verification.

## What the inherited Ziglings implementation actually does

Reviewed `build.zig`, `test/tests.zig`, and README.md from this repository's Git
HEAD, alongside the earlier Clings checker, verifier, patch generator, tests,
and CI. These are the inherited implementation in this checkout, not a claim
about every version of upstream Ziglings.

The build script confirms:

- `zig build` builds/runs/checks lessons sequentially and stops at the first
  compile, runtime, or output-check failure.
- Successful executable lessons write `.progress.txt`; a normal invocation
  skips lessons through the saved number.
- `-Dn=N` selects one lesson; `-Ds=N` starts a sequence at a chosen lesson.
- `-Drandom` selects one random lesson; `-Dreset` removes saved progress.
- Expectations and optional hints live in an explicit ordered exercise table.
  Executable output is checked for equality after normalization, usually on
  stderr and occasionally stdout.
- Healed-course mode and CLI tests use solution patches and temporary sources.
- GCC-like compilation alone is not the workflow: Zig's build runner supplies
  orchestration, state, diagnostics, and checking.

There are quirks to avoid copying: named/random executable checks also write
progress, so checking a later lesson can skip earlier unsolved lessons. Numeric
progress also cannot represent Clings' suffix identifiers. The inherited README
advertises some advanced commands that the reviewed build script does not
define; confirmed implementation behavior is the reference for this migration.

## Learner commands

| Inherited Ziglings | Native Clings |
| --- | --- |
| `zig build` | `make` |
| `zig build -Dn=19` | `make n=019` |
| `zig build -Ds=27` | `make s=027` |
| `zig build -Drandom` | `make random` |
| `zig build -Dreset` | `make reset` |
| CLI/build tests | `make test` |
| Full healed-course verification | `make verify` |

The executable also exposes direct commands:

```sh
./clings
./clings --exercise 032b
./clings --start 039
./clings --random
./clings --reset
./clings --list
./clings --all
```

Default `make` must always invoke the checker, even when the runner executable
is up to date. Exercise failures must propagate to Make as a failing command.
`make build` compiles only the runner; `make clean` removes build artifacts,
not learner changes or progress. Compiler override: `make CC=gcc-12`.
Make must pass that compiler choice to the runner as well as using it to build
the runner; otherwise exercise compilation could accidentally use another GCC.

## Progress semantics

- A fresh checkout starts at 001. Normal runs resume after the last successful
  lesson and continue until failure or the conclusion.
- Store the last passed identifier in a root-relative `.clings-progress` file,
  including its suffix: for example, `032b`. Locate it through the ordered
  registry rather than integer arithmetic.
- Advance progress only after successful compilation, execution, and checking
  in normal resume mode. Use a temporary file and rename for atomic updates.
- Single-lesson, random, explicit-start, list, full-check, and verification modes
  do not update normal progress. This prevents jumping past unsolved lessons.
- `--all` checks from the beginning without reading or changing progress.
- `--reset` removes progress only. It does not replace exercises with starters.
- Invalid saved state produces an actionable error; it must not silently skip
  lessons. The conclusion's identifier records completion.

## Implementation structure

Keep the implementation compact and share the checking engine:

```text
Makefile                 build, learner entry point, tests, verification
src/clings.c             CLI, lesson selection, resume loop, verification mode
src/runner.c / runner.h  process execution, temporary files, output checks
src/course.h             explicit ordered identifiers and filenames
tests/test_runner.c      native unit/regression tests
tests/test_cli.sh        actual executable/build/progress integration tests
tools/make_patch.sh      validated unified-diff generation
```

`src/course.h` is a normal C table, not generated code or a new config format.
It provides ordering, selection, and
coverage validation. Keep 032 before 032b/032c, and 033 before 033b. Validate
missing, extra, duplicate, or out-of-order lessons before claiming verification
success. Retain output expectations in the existing exercise comments.

### Native checking engine

- Use C11 and POSIX APIs on the documented Linux baseline. Define the required
  feature-test macros in the runner; identify these APIs as POSIX.
- Resolve the project root from the runner's location so external-directory
  invocation still works. Linux `/proc/self/exe` is an available approach,
  explicitly Linux-specific; build the runner as root-level `clings`.
- Use `mkdtemp` and copy course C files for each run. Keep the program's working
  directory and `argv[0]` compatible with file-reading and CLI lessons, including
  `./056_cli_args.out`. Cleanup must handle failure and interruption without
  following lesson-created symlinks outside the temporary directory.
- Invoke GCC with an argument array through `fork`/`execvp`, not a shell command
  string. Preserve the current C11 warnings, `-pthread`, and `-lm`.
- Display compiler diagnostics and runtime stderr directly. Capture stdout for
  checking. Use `poll`, a monotonic deadline, and `waitpid` so capture cannot
  deadlock and runtime/compile timeouts remain bounded.
- Put child processes in a process group; timeout and Ctrl+C handling terminate
  that group, reap the child, and clean temporary files. Signal handlers only
  set flags; cleanup occurs in normal control flow.
- Preserve the current three check directives: ordered `CHECK`, full-output
  `CHECK-EXACT`, and unordered `CHECK-ANY`. Missing expectations fail. Moving to
  a native runner must not silently weaken or reinterpret existing checks.
- Bound captured output with a clearly reported failure, as the inherited Zig
  runner does. Keep sanitizer detection fatal in maintainer mode.

The main engineering cost is correctly implementing process capture, timeouts,
cleanup, and progress in C. Make should remain a thin entry point: attempting to
encode this stateful behavior entirely in Make recipes would be harder to test.

## Completed tooling replacement

- The earlier scripted checker is replaced by `clings` and the Make entry point.
- Verification is `./clings --verify`, exposed as `make verify`.
  Apply existing patches with the standard `patch` utility, validate coverage,
  check all solved lessons and intentional starter failures, and ignore progress.
- Expose sanitizer verification as `make verify-sanitize`; reuse the same engine.
- Patch generation uses a quoted shell script and the native
  engine's maintainer-only `--check-file PATH` mode to validate a solved copy
  without progress changes, and `diff -u` to produce its patch. Treat
  diff exit 1 as a generated difference, 0 as an unchanged answer, and higher
  statuses as errors. Preserve original filenames in patch headers.
- The earlier regression cases are ported to native tests and shell CLI fixtures.
  Add saved-progress, reset, suffix, completion, random-selection, interrupted
  execution, and Make entry-point tests.
- CI and documentation use `make test`,
  `make verify`, and `make verify-sanitize` on the existing Ubuntu matrix.
- Update README.md, CONTRIBUTING.md, AGENTS.md, COURSE.md, solution instructions,
  and ignore rules. Ignore the native executable, build artifacts, and progress.

Learner dependencies become GCC, Make, and the system C/POSIX libraries.
Maintainer patch workflows also require standard shell utilities, `patch`, and
`diff`. No Python interpreter, package, script, or generated-code step is needed.

## Implementation order and acceptance

1. Build the native engine and port checking tests. Verify selection, compiler
   and runtime failures, output matching, timeouts, cleanup, and external paths.
2. Add Make entry points and saved progress. Verify repeated `make` runs resume
   correctly, including suffixes; failure never advances state; reset preserves
   learner edits; named/random/start runs cannot skip unsolved lessons.
3. Port verification and patch generation. All 97 solved files must pass on GCC
   11 and a newer GCC, with all 96 starters retaining tasks. A completed progress
   file must never shorten verification. Exercise sanitizer failure explicitly.
4. Replace tests/CI/docs and retire the scripted tooling. Run documented commands
   from a fresh disposable copy using native tools. Check that
   verification leaves learner sources unchanged and no data/executables behind.

Reuse the already verified lesson and solution work throughout. Complete this
as a tooling/workflow migration rather than rewriting the course again.

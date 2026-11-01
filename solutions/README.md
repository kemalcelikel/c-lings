# C solution patches

These are maintainer answers. Learners work in `exercises/`; patches preserve
the intentionally broken starter programs. The complete conclusion needs no patch.

Run from the root:

```sh
make verify
make verify-sanitize
make verify n=039
```

The native checker applies patches to temporary copies, validates exact coverage,
checks solved lessons, and confirms the original starters still fail. It never
reads or updates learner progress. Requirements: GCC, GNU Make, and `patch`.

To update an answer, place a solved file in a temporary answers directory,
preserving its filename and any other C sources it reads. Then run:

```sh
sh tools/make_patch.sh /path/to/answers/039_files_read.c
make verify
```

The shell script validates with the native checker and generates a unified diff
using `diff`. Missing, extra, malformed, and non-applicable patches fail course
verification. An invalid or unchanged answer does not overwrite its patch.

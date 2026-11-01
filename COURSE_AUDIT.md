# C course audit

## Summary

Reviewed all 97 committed lesson files, all 96 solution patches, the ordered
registry, and the native runner's checking contract at commit `47f855f`.
Used disposable copies of committed sources: the learner's local changes to
`exercises/001_hello.c` were excluded from maintenance checks and preserved.

The course is a good working baseline, but **not yet a complete C fundamentals
course**. Its main gaps are prerequisite ordering, missing C-specific topics,
and checks that do not always assess the stated task.

Evidence from this review:

- All 97 committed solved lessons pass ordinary verification and fatal
  address/undefined-behavior sanitizer verification.
- Sixteen edits violating stated tasks still pass the normal checker; details
  below. Many are valid C with identical output, so output checking alone cannot
  establish their requested type, qualifier, or implementation properties.
- The limited hash table returns a false hit for an absent empty-string key.
- Several lessons label already-complete code as learner problems.

The coverage checklist follows the C11 portions of the
[C language reference](https://en.cppreference.com/w/c/language.html).
Ziglings' useful model is core-language coverage plus selected library practice;
Clings should cover C's own model rather than reproduce Zig-only features or
match its exercise count. C23-only features are outside the current baseline.

## Coverage gaps

| Area | Current coverage | Needed work |
| --- | --- | --- |
| Basic scalar types and formats | Types appear throughout; detailed integers/floats arrive at 042/043 | Introduce char, int, unsigned, float/double, and matching output formats earlier |
| Operators | Comparisons at 008, logic in quiz 016, bits at 041, conversions at 044 | Dedicated precedence, short-circuiting, sequencing, promotions, signed/unsigned arithmetic, and overflow practice |
| Initialization | Array/string/struct initializers are shown | Teach partial aggregate initialization, automatic indeterminate values, static zero initialization, and C constant-expression rules |
| Scope and lifetime | Static locals at 060, borrowed views at 064 | Add block/function scope, shadowing, automatic/static/allocated lifetimes, and dangling-address examples |
| Pointer fundamentals | Good dereference/arithmetic coverage at 030–034 | Add NULL versus valid/non-NULL pointers, array decay versus sizeof, pointer differences, and ownership/aliasing |
| Functions and program structure | Prototypes briefly shown at 017/019 | Teach declarations versus definitions, headers, guards, translation units, linkage, and linker errors |
| Preprocessor | Includes throughout, macros at 053 | Add object-like constants, conditional compilation, include guards, and expression-argument tests |
| Strings and input | Strings at 004/007, files at 039/040, library functions at 082 | Add buffer capacity/NUL practice, standard streams/EOF, safe input, snprintf, and checked strtol conversion |
| Memory | Allocation and freeing at 036–038; byte copying at 070/083 | Add allocation-size/overflow checks, overlap-safe memmove, and effective learner-facing memory diagnostics |
| C11 features | Static assertions and atomics; _Generic only mentioned | Add runnable _Generic, _Alignas/_Alignof, and _Thread_local examples; make static assertions meaningful |
| Standard-library algorithms | Linked list and limited hash table | Add qsort and bsearch, with safe comparators and boundary cases |
| Concurrency | POSIX threads/mutexes/conditions plus C11 atomics | Explain data races and atomic ++ precisely; output counts alone do not prove synchronization |
| Opaque interfaces | Simulated in one file at 074 | Demonstrate a real public header/private implementation boundary |

Later additions can cover compound literals, restrict, _Noreturn, richer atomic
ordering, date/time, and additional string/character utilities. Implementation-
optional facilities such as C11 VLAs, complex arithmetic, and threads.h need
explicit support notes. GNU SIMD/packing and other POSIX topics remain useful
extensions, but should not take priority over missing fundamentals.

## Confirmed acceptance gaps

Each experiment first applied the official patch and confirmed the answer passed,
then made the indicated edit in a temporary solved copy. All sixteen edited
copies also passed the native checker's ordinary checking mode.

| Lesson | Task-violating edit accepted |
| --- | --- |
| 009 | Change the untested false-branch price from 20 to 999 |
| 010 | Remove the loop's printed sequence; the final n=1024 still passes |
| 027 | Replace assert(0) with assert(1); the default branch never runs |
| 032c | Remove required const qualifiers from p2 and p3 |
| 036 | Replace free(p) with free(NULL), leaking the allocation |
| 043 | Use float for both values where double is requested; rounded output is unchanged |
| 047 | Replace the shared-storage union with a struct |
| 053 | Define MAX as its second argument and MIN as its first; only ordered inputs are tested |
| 056 | Loop only once and always use argv[0]; no extra arguments are supplied |
| 057 | Look up PATH instead of USER; CHECK only requires the greeting prefix |
| 067 | Replace volatile with static; the current unoptimized compilation still stops |
| 068 | Replace inline with signed; runtime output cannot demonstrate inline usage |
| 081 | Alias Byte to unsigned short rather than unsigned char |
| 088 | Declare is_valid as int instead of bool |
| 091 | Declare counter as int; GCC's atomic macro still performs an atomic operation |
| 094 | Give both boolean fields two bits rather than one; neither field is checked |

Sanitizer mode rejects the leaked allocation in the 036 experiment. However,
ordinary learner runs do not automatically enable it. Sanitizing the official
solution does not establish that a learner's different answer is memory-safe.
The 091 experiment concerns the requested atomic declaration, not a demonstrated
runtime race: GCC's macro uses an atomic builtin even with the plain-int pointer.

Fix checks using meaningful inputs, observable postconditions, type/compile
probes where appropriate, and better lesson design. Do not compare learner
source text to the official solution: legitimate equivalent C answers must pass.
Some concepts, especially inline hints and prohibited const writes, cannot be
established from successful stdout alone.

## Confirmed logic defect: 071

`exercises/071_hashmap.c` accepts empty keys through put(), but an initial
get("") returns 0 instead of the documented missing result -1. The empty table
has zero-initialized keys/values, and get() has no occupied-entry distinction.
A temporary probe expecting -1 exited with failure and printed the actual 0.

Either reject empty keys consistently and document that restriction, or track
occupancy. Collision overwriting is already disclosed; implementing collision
handling should be a separate subsequent lesson/addition, not quietly claimed
as existing coverage.

**Fixed in lesson 071:** entries now track occupancy, retaining support for empty
keys and stored value 0. Exact checks cover an absent empty key, its insertion,
the named keys, and an ordinary miss. Removing the occupancy guard reproduces
the old false hit and is now rejected. Collision resolution remains a separate
planned addition.

## Individual lesson review

**Keep** means no urgent change identified, not exhaustive proof of correctness.
**Explain** means improve prerequisites, wording, or problem labels. **Check**
means strengthen assessment. **Rework** means the stated concept needs a more
meaningful exercise or supporting verification capability.

| ID | Review | Recommended action |
| --- | --- | --- |
| 001 | Keep | Clear first header task; preserve local learner edits |
| 002 | Explain | Explain the first %d use and const versus a C constant expression |
| 003 | Keep | Useful const/index/array-size tasks; add array-decay practice elsewhere |
| 004 | Check | Use complete output so a string beginning with d cannot stand in for the character |
| 005 | Keep | Focused multidimensional indexing |
| 006 | Keep | Clear adjacent-literal task with exact checks |
| 007 | Keep | Useful indexing/string-termination practice |
| 008 | Keep | Clear truth/equality introduction; follow with logic and bool fundamentals |
| 009 | Check | Exercise both discount branches |
| 010 | Check | Check the full loop sequence as well as the final value |
| 011 | Check | Same sequence gap as 010 |
| 012 | Keep | Distinguishes skipping iterations from ending the loop |
| 013 | Keep | Break behavior is observable |
| 014 | Explain | Explain hardcoded length versus sizeof/strlen; indexing is one iteration idiom |
| 015 | Explain | Explain unsigned shift bounds and avoid claiming C always iterates with an index |
| 016 | Keep | Useful FizzBuzz quiz; logical-operator foundations should precede it |
| 017 | Explain | Explain void parameters and prototypes; add an actual declaration task |
| 018 | Explain | Unsigned types/formatting should already be familiar |
| 019 | Explain | Bridge array decay and declarations before expecting pointer terminology |
| 020 | Explain | Distinguish this enum classifier from conventional success/error status codes |
| 021 | Keep | Explicit output-parameter preview and bounded sample inputs |
| 022 | Keep | Checks all three statuses; switch preview is explained |
| 023 | Explain | Use (void) in examples; consider observable evidence that later work is skipped |
| 024 | Explain | Clearly label simulated resources and provided code versus actual tasks |
| 025 | Keep | Exact check covers the default case |
| 026 | Keep | Good fallthrough example; a later statement could clarify break versus return |
| 027 | Rework | The requested failed assertion is never exercised |
| 028 | Keep | Named enum operations with observable results |
| 029 | Keep | Struct fields and designated initialization are introduced clearly |
| 030 | Keep | Clear addresses/dereferencing introduction |
| 031 | Keep | Typed pointer tasks are constrained by their actual use |
| 032 | Keep | Pointer mutation is checked in both objects |
| 032b | Explain | Allocation is a preview and already implemented; repair problem numbering |
| 032c | Rework | Required qualifiers are not assessed by the commented-out negative examples |
| 033 | Keep | Pointer arithmetic includes appropriate bounds/one-past notes |
| 033b | Explain | Introduce float/double earlier; retain the correct object-pointer conversion caveat |
| 034 | Keep | Struct-pointer mutation has useful intermediate checks |
| 035 | Keep | Tagged union checks both active representations |
| 036 | Check | Freeing must be verified through memory diagnostics, not the printed value |
| 037 | Check | Same leak gap; clarify that calloc zeroes bits, not every possible type's semantic zero |
| 038 | Check | Assess allocation bounds under diagnostics; teach invalidated aliases after successful resize |
| 039 | Explain | First line // is uninformative; explain fgets capacity, newline, EOF/error, and closing |
| 040 | Keep | Good write/readback verification and checked failure paths |
| 041 | Explain | Add shift/clear/toggle practice separately; listed operators exceed exercised operators |
| 042 | Explain | Supplement literals with actual ranges, promotions, and signedness practice |
| 043 | Check | Choose precision-sensitive inputs/output that distinguish float from double |
| 044 | Explain | Explain why unsigned narrowing produces 232 and the limits of conversions |
| 045 | Keep | Correct nested-loop goto example; visit-count checks could improve the demonstration |
| 046 | Explain | Reinforce sentinel existence/domain and capacity versus string length |
| 047 | Check | Demonstrate actual shared storage without reading an inactive union representation |
| 048 | Explain | Give basic function-pointer practice before struct-based dispatch |
| 049 | Check | Linking is exercised, but free(NULL) can evade ordinary cleanup assessment |
| 050 | Check | Check all tokens/punctuation, not just three tokens and the count; explain saved strtok state |
| 051 | Keep | Correct argument lifetimes, joins, POSIX labels, and unordered output |
| 052 | Explain | Add default argument promotions and matching va_arg types; avoid implying output proves va_end |
| 053 | Check | Test reversed/equal arguments and expression arguments; retain side-effect warnings |
| 054 | Keep | Keep as optional bitwise practice; the ordinary temporary-variable idiom is already preferred |
| 055 | Keep | Good unsigned masks and safe ctype use; uppercase-only coverage would improve breadth |
| 056 | Rework | Supply real arguments so argc and indexed iteration are exercised |
| 057 | Rework | Controlled environment cases should verify the requested lookup and absent-value handling |
| 058 | Explain | State nonnegative/bounded input assumptions; include 0! and 1! |
| 059 | Keep | Callback dispatch is observed for both formats |
| 060 | Explain | Relate persistence to earlier scope/storage-duration concepts; use (void) in examples |
| 061 | Keep | Controlled raise, signal flag, and handler restrictions are appropriate |
| 062 | Keep | Working math introduction; more rounding inputs are a useful later improvement |
| 064 | Check | Check exact slice boundaries/lengths, not just prefixes of their printed contents |
| 065 | Check | Verify four-element vector width, not only the first four outputs; keep extension label |
| 066 | Keep | Good POSIX write example with partial-transfer/EINTR handling |
| 067 | Rework | Volatile needs assessment beyond the current unoptimized run |
| 068 | Rework | Teach real linkage behavior or present inline explicitly as an illustrative hint |
| 069 | Check | Clarify conflicting accesses/data races; a final count is not proof of mutex correctness |
| 070 | Keep | Good type-erased byte copying; introduce raw-memory basics earlier and add _Generic separately |
| 071 | Rework | Fix absent empty-key lookup; add missing-key tests; collision handling remains missing |
| 072 | Rework | Retain/decrement logic is already filled in; restore substantive counting tasks and verify cleanup |
| 073 | Explain | GCC packing is covered; ISO C11 alignment syntax still needs its own lesson |
| 074 | Rework | Demonstrate real opacity across a header/private translation unit; verify destruction |
| 075 | Keep | Useful static-lifetime/shared-instance application; treat as an optional pattern |
| 076 | Keep | Meaningful state progression; empty range and repeated completion would add useful cases |
| 077 | Explain | Keep non-local-jump restrictions and clarify exception terminology; exclude the forbidden continuation |
| 078 | Keep | Useful wrapper/callback application, not a separate C language feature |
| 079 | Explain | Label as review; basic function pointers should precede 048/059 |
| 080 | Check | Demonstrate initially-false post-test behavior; check the whole sequence and stop boundary |
| 081 | Check | Verify the alias's intended type/width; distinguish an anonymous typedef from a struct tag |
| 082 | Keep | Good string operations with explicit capacity/overlap requirements |
| 083 | Check | Initialize known nonzero contents before memset so short byte counts do not read indeterminate ints |
| 084 | Explain | Only saving errno is currently a task; fix labels around already-complete perror/printing code |
| 085 | Explain | Preserve the alias caveat; mark the already-provided NULL check as supplied context |
| 086 | Keep | Checked same-program binary round trip, with appropriate portability limitations |
| 087 | Explain | Only SEEK_SET is a task; add origin practice or label the other operations as provided |
| 088 | Check | Demonstrate bool's nonzero-to-one conversion and introduce it earlier |
| 089 | Check | Undersized allocations need diagnostics; add general size/overflow practice elsewhere |
| 090 | Rework | Replace language-guaranteed tautologies with an actual program invariant |
| 091 | Check | Verify the atomic declaration; explain that ++ on an atomic object is itself atomic |
| 092 | Keep | Good predicate loop, handshake, and spurious-wakeup explanation |
| 093 | Check | Validate complete byte representations/classification, not just output prefixes |
| 094 | Check | Exercise both one-bit fields, using defined unsigned conversion behavior |
| 999 | Keep | Complete conclusion; qualify the absolute machine-control wording during final polish |

## Recommended implementation sequence

1. **Fix the concrete 071 lookup defect.** Completed as its own lesson change.
2. **Improve existing observable checks**, starting with 009, 010, 011, 043,
   047, 053, 080, 083, and 094. One lesson per commit, with its updated patch.
3. **Fill early foundations:** scalar types/formats, logic/precedence/short
   circuiting, initialization, scope/lifetimes, NULL/array decay, prototypes,
   and basic typedefs/bool. Preserve existing identifiers; insert new suffix
   lessons where their prerequisites belong rather than renumbering the course.
4. **Add only necessary native fixture support**, in separate checker commits:
   actual arguments, deterministic stdin/environment, and companion headers/
   linked sources. The current runner copies only .c files, compiles one source,
   supplies no extra arguments, and has no deterministic input/environment cases.
   Multi-file support also affects solution application/generation, not just GCC.
5. **Rework dependent lessons:** genuine headers/linkage/opacity, 056/057 input
   cases, and assessment of memory and compile-time/type properties. Choose
   diagnostics/type probes explicitly; do not claim stdout validates every rule.
6. **Add C11 and selected-library coverage:** _Generic (063 is an available
   slot if deliberately registered), standard alignment, thread-local storage,
   safe input/strtol, snprintf, memmove, qsort, and bsearch. Each addition is
   its own commit; registry, counts, inventory, and applicable tests move with it.
7. **Optional breadth** comes after these foundations, not before them.

Existing learners may already be beyond a newly inserted prerequisite. They can
select that new lesson explicitly; never reset their source files to force a
new curriculum order.

## Per-lesson commit and verification rule

- Finish and verify one lesson fix/addition, then commit it before starting the
  next. Include its starter, minimal solution patch, and only directly required
  registry/inventory/count/test updates. Do not combine unrelated lesson changes.
- Shared checker capabilities get separate focused commits before dependent
  lessons. Fixing a lesson does not justify staging another learner's answer.
- Inspect status/diffs first. If the target has learner edits, work from an
  isolated committed copy rather than overwriting or resetting those edits.
- Regenerate patches from temporary solved copies with original filenames.
- Check the changed lesson and full solved course, including sanitizers. Use
  native regression tests for registry/checker changes. Add meaningful cases
  demonstrating that the specific previous mistake is now rejected.
- With solved learner files in the working tree, full maintenance verification
  must run against a clean committed/staged snapshot containing the intended
  maintenance change. Normal verification deliberately rejects already-solved
  starters; that is not a course regression. A snapshot of the reviewed index
  can be exported using git write-tree/git archive without altering learner files.
- Stage only the intended lesson change. Suggested subjects: "Fix lesson 053
  macro checks" or "Add lesson 063 generic selection".

This pass records the audit and work sequence. It does not solve or rewrite
learner lessons.

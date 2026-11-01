# Course inventory

Clings has **96 learner exercises and one complete conclusion**. Numeric
identifiers precede their suffixes: 032, 032b, 032c, 033, 033b. There is no 063.
Each starter contains a deliberate task; each solved version has a C patch in
`solutions/`, except the already complete conclusion.

## Teaching approach

Lessons explain general C rules and leave task-specific repairs to the learner.
Examples illustrate syntax with separate names and values; expected output
describes the goal, not the implementation. Quizzes 007, 016, and 019 combine
earlier concepts with less scaffolding. Repeated topics provide further practice
rather than repeating a full answer beside a placeholder.

Some supplied code previews later topics: pointer declarations in 004 and array
parameters in 019, enums in 020, pointer output parameters in 021, switch in 022,
and allocation in 032b. These previews are explained where they appear; the
learner's task should remain solvable from those explanations and prior lessons.
Later dedicated lessons revisit the concepts in more depth. C11 verification
checks compilation and behavior, not whether an optional optimization occurred.

## Platform contract

The baseline is Linux, GNU Make, and GCC 11+ with C11, common warnings treated
as errors, `-pedantic`, `-pthread`, and `-lm`. Ordinary language/library lessons
use ISO C. POSIX APIs and compiler extensions are identified in the table.

- 042 and 093 assume available exact-width integer types and 8-bit bytes.
  042 and 055 assume ASCII-compatible character codes.
- 065 uses GCC vector attributes and assumes 4-byte floats. SIMD instruction
  selection depends on the compiler and target.
- 073 uses GCC packing attributes; ordinary struct sizes remain ABI-dependent.
- 057 handles an absent USER variable with a guest greeting. 084 checks POSIX
  ENOENT symbolically, without matching locale-specific messages.
- 086 writes/reads a struct within the same program, not portable serialization.
  087 seeks a regular file in the supported POSIX environment.
- Thread output may be unordered. 092 uses a predicate handshake, not sleeps.
- 071 is a limited hash table: collisions overwrite, keys are bounded, and -1
  means missing. 072 and 075 demonstrate single-threaded ownership/shared state.

## Lessons

| Identifier | File | Concept / special requirement |
| --- | --- | --- |
| 001 | `001_hello.c` | Entry point and standard headers |
| 002 | `002_variables.c` | Variables and const |
| 003 | `003_arrays.c` | Array indexing and sizeof |
| 004 | `004_strings.c` | Strings, characters, and printf formats |
| 005 | `005_multidimensional_arrays.c` | Multidimensional indexing |
| 006 | `006_multiline_strings.c` | Adjacent string literals |
| 007 | `007_quiz.c` | Array indexing quiz |
| 008 | `008_if.c` | Conditions and equality |
| 009 | `009_ternary.c` | Conditional operator |
| 010 | `010_while.c` | While loops |
| 011 | `011_for.c` | For loops |
| 012 | `012_continue.c` | Skipping iterations |
| 013 | `013_break.c` | Ending a loop |
| 014 | `014_array_loop.c` | Iterating through arrays |
| 015 | `015_array_loop_index.c` | Indices and bit positions |
| 016 | `016_quiz2.c` | FizzBuzz quiz |
| 017 | `017_functions.c` | Return types |
| 018 | `018_functions2.c` | Function parameters |
| 019 | `019_quiz3.c` | Functions and arrays quiz |
| 020 | `020_enum_errors.c` | Enumerated status codes |
| 021 | `021_return_codes.c` | Status returns and output parameters |
| 022 | `022_handle_errors.c` | Handling individual errors |
| 023 | `023_propagate_errors.c` | Propagating failure |
| 024 | `024_cleanup.c` | Goto cleanup paths |
| 025 | `025_switch.c` | Cases and default |
| 026 | `026_switch_break.c` | Switch fallthrough |
| 027 | `027_unreachable.c` | Executed debugging assumptions and unreachable paths |
| 028 | `028_enums.c` | Enumerated operations |
| 029 | `029_structs.c` | Struct members |
| 030 | `030_pointers.c` | Addresses and dereferencing |
| 031 | `031_pointer_types.c` | Typed pointers |
| 032 | `032_pointers_modify.c` | Modifying through pointers |
| 032b | `032b_double_pointers.c` | Pointer output parameters and allocation |
| 032c | `032c_const_pointers.c` | Compiler-enforced const pointer operations |
| 033 | `033_pointers_arithmetic.c` | Pointer arithmetic and bounds |
| 033b | `033b_void_pointers.c` | Generic object pointers |
| 034 | `034_struct_methods.c` | Struct pointer parameters |
| 035 | `035_unions.c` | Tagged unions |
| 036 | `036_malloc.c` | Allocation and free |
| 037 | `037_calloc.c` | Zero-initialized allocation |
| 038 | `038_realloc.c` | Resizing allocations |
| 039 | `039_files_read.c` | Reading the lesson's own source file |
| 040 | `040_files_write.c` | Writing and checking file contents |
| 041 | `041_bit_ops.c` | Bitwise operators |
| 042 | `042_integers.c` | Integer literals and fixed-width types |
| 043 | `043_floats.c` | Floating-point types and formatting |
| 044 | `044_coercions.c` | Conversions and integer division |
| 045 | `045_goto_labels.c` | Exiting nested loops |
| 046 | `046_sentinels.c` | Sentinel-terminated sequences |
| 047 | `047_struct_init.c` | Designated initializers and anonymous unions |
| 048 | `048_interfaces.c` | Function-pointer dispatch |
| 049 | `049_linked_list.c` | Linked-list ownership |
| 050 | `050_strtok.c` | Tokenization |
| 051 | `051_pthreads.c` | POSIX thread creation and joining |
| 052 | `052_variadic.c` | Variadic argument lists |
| 053 | `053_macros.c` | Macro expansion and parentheses |
| 054 | `054_bit_swap.c` | XOR swap and its limitations |
| 055 | `055_bit_flags.c` | Bit flags and character handling |
| 056 | `056_cli_args.c` | argc and argv, no extra arguments |
| 057 | `057_env_vars.c` | Environment variables |
| 058 | `058_recursion.c` | Base cases and recursion |
| 059 | `059_callbacks.c` | Callback parameters |
| 060 | `060_static_variables.c` | Static local storage |
| 061 | `061_signals.c` | ISO C signal and raise |
| 062 | `062_math_library.c` | Math functions, linked with -lm |
| 064 | `064_slices.c` | Borrowed pointer/length views |
| 065 | `065_vectors.c` | GCC vector extension |
| 066 | `066_low_level_io.c` | POSIX write and partial transfers |
| 067 | `067_volatile.c` | Signal flags and POSIX alarm |
| 068 | `068_inline.c` | Static inline, linkage, and a helper's behavior |
| 069 | `069_mutex.c` | POSIX mutex protection |
| 070 | `070_generics_void.c` | Byte-oriented generic operations |
| 071 | `071_hashmap.c` | Limited hash-table example |
| 072 | `072_ref_counting.c` | Manual shared ownership |
| 073 | `073_alignment.c` | Alignment and GCC packing extension |
| 074 | `074_opaque_pointers.c` | Opaque interface, demonstrated in one file |
| 075 | `075_singleton.c` | Shared static instance |
| 076 | `076_generator.c` | Stateful iteration |
| 077 | `077_setjmp_exceptions.c` | Non-local jumps and their restrictions |
| 078 | `078_decorators.c` | Function wrappers |
| 079 | `079_function_pointers.c` | Function-pointer practice |
| 080 | `080_do_while.c` | Post-test loops |
| 081 | `081_typedef.c` | Type aliases |
| 082 | `082_string_libs.c` | String functions and buffer capacity |
| 083 | `083_memory_libs.c` | Byte counts and memory functions |
| 084 | `084_errno.c` | POSIX fopen errors and saved errno |
| 085 | `085_safe_memory.c` | Dangling pointers and double free |
| 086 | `086_binary_io.c` | Checked binary round trip |
| 087 | `087_file_seek.c` | Regular-file seeking |
| 088 | `088_stdbool.c` | Boolean types |
| 089 | `089_flexible_array.c` | Flexible array allocation |
| 090 | `090_static_assert.c` | Compile-time assertions |
| 091 | `091_atomics.c` | C11 atomics with POSIX worker threads |
| 092 | `092_cond_var.c` | POSIX condition variables and predicates |
| 093 | `093_endianness.c` | Inspecting object representations |
| 094 | `094_bitfields.c` | Bitfield widths and unsigned conversion |
| 999 | `999_the_end.c` | Complete conclusion, no solution patch |

## Verification

`make verify` uses the same native C runner as learner files. It also checks
that each starter still fails before applying its patch; the conclusion must
pass directly. Missing course identifiers, missing/extra patches, invalid
patches, compiler/runtime failures, and incorrect output fail verification.
Sanitizer mode makes detected address and undefined-behavior errors fatal.
Saved learner progress is ignored during verification. `make verify-sanitize`
enables sanitizers; `make test` runs native and shell regression tests.
See [CONTRIBUTING.md](CONTRIBUTING.md).

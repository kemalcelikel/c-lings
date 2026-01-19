# Clings

Welcome to **Clings**! This project contains a series of tiny broken C programs (and some nasty bugs). By fixing them, you'll learn how to read and write robust, system-level C code.

This project is directly inspired by the brilliant [Ziglings](https://github.com/ratfactor/ziglings) and [Rustlings](https://github.com/rust-lang/rustlings) projects.

## Intended Audience

This is designed for:
*   Beginners who want to learn C syntax and pointers.
*   Developers coming from high-level languages (Python, JS) who want to understand memory and low-level logic.
*   Students who want to practice standard C idioms and design patterns.

You are **not** expected to have prior experience with systems programming. We start from "Hello World".

## Getting Started

### 1. Install Prerequisites

You need a C compiler and Python 3 (for the test runner).

**Linux (Debian/Ubuntu):**
```bash
sudo apt update
sudo apt install build-essential python3
```

**macOS:**
```bash
xcode-select --install
```

**Windows:**
We recommend using [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/en-us/windows/wsl/install). If using MinGW or MSVC natively, your mileage may vary with the threading and atomic exercises.

### 2. Verify Installation

Check that you have `gcc` installed and it supports C11 (most modern versions do).
```bash
gcc --version
```

### 3. Start Coding!

Enter the directory and run the check script:

```bash
cd exercises_c
./check.py
```

## How to Work

The `check.py` script is your guide. It attempts to compile the exercises in order.

1.  **Run `./check.py`**.
2.  It will stop at the **first** exercise that fails to compile or runs incorrectly.
3.  **Read the error message**. The compiler is your friend (usually).
4.  **Open the file** (e.g., `001_hello.c`).
5.  Look for comments, `???` placeholders, or logic bugs.
6.  **Fix the code**.
7.  **Run `./check.py` again**.
8.  Repeat until you reach **The End**!

## "It works on my machine, why does it fail here?"

Clings uses **Strict Compilation Flags** to enforce good habits. We compile with:

```bash
gcc -std=c11 -Wall -Wextra -Werror -pedantic ...
```

*   **-Wall -Wextra:** Enable all warnings.
*   **-Werror:** Treat warnings as errors. If you have an unused variable or a mismatched type, the build **will fail**. This is intentional. C is unforgiving; we want you to write clean code from day one.
*   **-pedantic:** Enforce strict ISO C compliance. No non-standard compiler extensions allowed unless explicitly noted.
*   **-std=c11:** We use the C11 standard to support features like Atomics (`stdatomic.h`) and Static Assertions.

### Common Issues & Fixes

*   **Implicit declaration of function...**: You forgot to `#include` the right header file (e.g., `<stdio.h>` for `printf`, `<stdlib.h>` for `malloc`).
*   **Unused variable...**: You declared a variable but didn't use it. Either use it, remove it, or silence the warning by casting to void: `(void)my_var;`.
*   **Comparison between signed and unsigned**: C warns about this because it can lead to wrap-around bugs. Cast your types explicitly or change the variable types to match.
*   **Undefined reference to pthread_...**: Ensure you are running on a system that supports POSIX threads (Linux/macOS). The check script automatically links `-lpthread`, but this library might be missing on bare-bones Windows setups.

## The Exercises

### Basics
*   [x] `001_hello.c`: Basic structure and includes.
*   [x] `002_variables.c`: Variables and constants.
*   [x] `003_arrays.c`: Arrays and length calculation.
*   [x] `004_strings.c`: Strings vs Characters.
*   [x] `005_multidimensional_arrays.c`: 2D Arrays.
*   [x] `006_multiline_strings.c`: String concatenation.
*   [x] `007_quiz.c`: Array indexing quiz.

### Control Flow
*   [x] `008_if.c`: If statements and booleans.
*   [x] `009_ternary.c`: The ternary operator.
*   [x] `010_while.c`: While loops.
*   [x] `011_for.c`: For loops.
*   [x] `012_continue.c`: Continue statement.
*   [x] `013_break.c`: Break statement.
*   [x] `014_array_loop.c`: Looping over arrays.
*   [x] `015_array_loop_index.c`: Loops with index.
*   [x] `016_quiz2.c`: FizzBuzz.

### Functions & Error Handling
*   [x] `017_functions.c`: Basic functions.
*   [x] `018_functions2.c`: Functions with parameters.
*   [x] `019_quiz3.c`: Functions and arrays.
*   [x] `020_enum_errors.c`: Error handling with Enums.
*   [x] `021_return_codes.c`: Error handling with return codes and pointers.
*   [x] `022_handle_errors.c`: Handling specific errors with switch.
*   [x] `023_propagate_errors.c`: Bubbling up errors.
*   [x] `024_cleanup.c`: Resource cleanup with goto.

### Advanced Control Flow
*   [x] `025_switch.c`: Switch statements.
*   [x] `026_switch_break.c`: Switch fallthrough (the missing break).
*   [x] `027_unreachable.c`: Asserting unreachable code.
*   [x] `080_do_while.c`: The do-while loop.
*   [x] `045_goto_labels.c`: Breaking nested loops with goto.
*   [x] `058_recursion.c`: Recursion.

### Types & Structs
*   [x] `028_enums.c`: Enumerations.
*   [x] `029_structs.c`: Structures.
*   [x] `047_struct_init.c`: Designated initializers and anonymous types.
*   [x] `081_typedef.c`: Type aliasing with typedef.
*   [x] `088_stdbool.c`: Boolean type (C99).
*   [x] `094_bitfields.c`: Bitfields in structs.

### Pointers (The Hard Part)
*   [x] `030_pointers.c`: Introduction to Pointers.
*   [x] `031_pointer_types.c`: Pointer types.
*   [x] `032_pointers_modify.c`: Modifying values via pointers.
*   [x] `032b_double_pointers.c`: Pointer to a Pointer.
*   [x] `032c_const_pointers.c`: Const pointers vs Pointers to const.
*   [x] `033_pointers_arithmetic.c`: Pointer arithmetic.
*   [x] `033b_void_pointers.c`: Generic void pointers.
*   [x] `034_struct_methods.c`: Simulating methods with pointers.

### Memory & Unions
*   [x] `035_unions.c`: Unions and Tagged Unions.
*   [x] `036_malloc.c`: Dynamic memory allocation.
*   [x] `037_calloc.c`: Zero-initialized allocation.
*   [x] `038_realloc.c`: Resizing memory.
*   [x] `049_linked_list.c`: Dynamic nodes and memory.
*   [x] `083_memory_libs.c`: Standard memory library functions.
*   [x] `085_safe_memory.c`: Avoiding memory bugs (Double free, etc).
*   [x] `089_flexible_array.c`: Flexible Array Members (C99).

### Numbers & Bits
*   [x] `041_bit_ops.c`: Bitwise operations.
*   [x] `042_integers.c`: Integer literals and stdint.h.
*   [x] `043_floats.c`: Double and float precision.
*   [x] `044_coercions.c`: Type casting.
*   [x] `054_bit_swap.c`: XOR swap trick.
*   [x] `055_bit_flags.c`: Bit flags and Pangrams.
*   [x] `062_math_library.c`: Using math.h.
*   [x] `093_endianness.c`: Detecting system endianness.

### Strings & I/O
*   [x] `039_files_read.c`: Reading files.
*   [x] `040_files_write.c`: Writing files.
*   [x] `046_sentinels.c`: Sentinel-terminated sequences.
*   [x] `050_strtok.c`: String tokenization.
*   [x] `056_cli_args.c`: Command line arguments.
*   [x] `057_env_vars.c`: Environment variables.
*   [x] `066_low_level_io.c`: write() system call.
*   [x] `082_string_libs.c`: Standard string library functions.
*   [x] `084_errno.c`: Error reporting with errno.
*   [x] `086_binary_io.c`: Binary file I/O with fread/fwrite.
*   [x] `087_file_seek.c`: File positioning with fseek.

### Advanced C Features
*   [x] `048_interfaces.c`: Polymorphism with function pointers.
*   [x] `052_variadic.c`: Variable arguments.
*   [x] `053_macros.c`: Preprocessor macros.
*   [x] `059_callbacks.c`: Function pointers as callbacks.
*   [x] `060_static_variables.c`: Static local variables.
*   [x] `067_volatile.c`: The volatile keyword.
*   [x] `068_inline.c`: Inline functions.
*   [x] `079_function_pointers.c`: Basic function pointers.
*   [x] `090_static_assert.c`: Compile-time assertions (C11).

### Concurrency
*   [x] `051_pthreads.c`: Multi-threading.
*   [x] `061_signals.c`: Signal handling.
*   [x] `069_mutex.c`: Thread synchronization with Mutexes.
*   [x] `091_atomics.c`: Atomic operations (C11).
*   [x] `092_cond_var.c`: Thread condition variables.

### Design Patterns
*   [x] `064_slices.c`: Simulating slices with structs.
*   [x] `065_vectors.c`: SIMD vector extensions.
*   [x] `070_generics_void.c`: Generic functions with void pointers.
*   [x] `071_hashmap.c`: Simple hash map implementation.
*   [x] `072_ref_counting.c`: Manual reference counting.
*   [x] `073_alignment.c`: Struct alignment and packing.
*   [x] `074_opaque_pointers.c`: Encapsulation with Opaque Pointers.
*   [x] `075_singleton.c`: Singleton pattern.
*   [x] `076_generator.c`: Simulating generators with state machines.
*   [x] `077_setjmp_exceptions.c`: Exception handling with setjmp/longjmp.
*   [x] `078_decorators.c`: Decorator pattern using function wrappers.

### Conclusion
*   [ ] `999_the_end.c`: The conclusion.

Good luck and happy coding!

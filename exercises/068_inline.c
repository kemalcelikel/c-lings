//
// The 'inline' keyword is a hint to the compiler to replace the
// function call with the actual code of the function.
// This can improve performance for very small, frequently called functions.
// It is not a guarantee of inlining. Use static inline for a definition with
// internal linkage, avoiding the need for a separate external definition.
//

#include <stdio.h>

// Complete this small internal-linkage helper with the function specifier
// discussed above, and implement its computation. Inlining is still optional.
static ??? int square(int x) {
    return ???;
}

int main(void) {
    int numbers[] = { -3, 0, 5 };
    for (int i = 0; i < 3; i++) {
        int n = numbers[i];
        printf("Square of %d is %d\n", n, square(n));
    }
    return 0;
}

// CHECK-EXACT: Square of -3 is 9
// CHECK-EXACT: Square of 0 is 0
// CHECK-EXACT: Square of 5 is 25

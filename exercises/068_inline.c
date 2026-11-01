//
// The 'inline' keyword is a hint to the compiler to replace the
// function call with the actual code of the function.
// This can improve performance for very small, frequently called functions.
// It is not a guarantee of inlining. Use static inline for a definition with
// internal linkage, avoiding the need for a separate external definition.
//

#include <stdio.h>

// (Problem 1)
// Add the inline keyword to this internal-linkage function.
static ??? int square(int x) {
    return x * x;
}

int main(void) {
    int n = 5;
    printf("Square of %d is %d\n", n, square(n));
    return 0;
}

// CHECK: Square of 5 is 25

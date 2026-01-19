//
// The 'inline' keyword is a hint to the compiler to replace the
// function call with the actual code of the function.
// This can improve performance for very small, frequently called functions.
//

#include <stdio.h>

// (Problem 1)
// Suggest to the compiler that this function should be inlined.
inline int square(int x) {
    return x * x;
}

int main(void) {
    int n = 5;
    printf("Square of %d is %d\n", n, square(n));
    return 0;
}

// CHECK: Square of 5 is 25

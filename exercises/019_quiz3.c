//
// Quiz time: combine function declarations, parameters, loops, and returns.
//
// In C, when you pass an array to a function, you usually
// need to pass its size as well. The parameter below is a pointer to its
// first element, not a copy of the array. This is a preview of lesson 030;
// the traversal is supplied so the task uses the concepts already studied.
//
//     void foo(int *arr, int size) { ... }
//

#include <stdio.h>

// Forward declarations
void printPowersOfTwo(int *numbers, int size);
int twoToThe(int number);

int main(void) {
    int my_numbers[] = { 0, 1, 5, 6, 7, 8 };

    // Include zero and one to exercise the boundary cases of the computation.
    printPowersOfTwo(my_numbers, 6);
    printf("\n");
    return 0;
}

// CHECK-EXACT: 1 2 32 64 128 256

// (Problem 1)
// Complete this definition to agree with its earlier declaration.
??? printPowersOfTwo(int *numbers, int size) {
    for (int i = 0; i < size; i++) {
        int n = numbers[i];
        printf("%d ", twoToThe(n));
    }
}

// (Problem 2)
// Compute an integer power of two using a loop, then return the result.
// The caller supplies small nonnegative exponents; do not use shifts here.
int twoToThe(int number) {
    ???;
}

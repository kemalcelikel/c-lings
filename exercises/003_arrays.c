//
// Let's learn some array basics.
//
// In C, arrays are declared like this:
//
//     int foo[3] = { 42, 108, 5423 };
//
// You can also let the compiler infer the size:
//
//     int foo[] = { 42, 108, 5423 };
//
// Get values using array[index]:
//
//     int bar = foo[2]; // 5423
// Indices start at zero: the first element has index 0.
//
// Set values:
//
//     foo[2] = 16;
//
// sizeof gives an object's size in bytes. For an actual array, dividing
// its byte size by one element's byte size gives the element count.
// This does not work on a pointer: sizeof then gives the pointer's size.
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // The array's declaration must allow the operation below.
    const int some_primes[] = { 1, 3, 5, 7, 11, 13, 17, 19 };

    // We want to change the first element to 2.
    some_primes[0] = 2;

    int first = some_primes[0];

    // (Problem 2)
    // Access the fourth element. Count from the array's first index.
    int index_of_fourth = ???;
    int value_of_fourth = some_primes[index_of_fourth];

    // (Problem 3)
    // Calculate the length.
    // sizeof produces size_t; print it with %zu.
    size_t length = 0; // Derive this from the array, not a hardcoded count.

    printf("First: %d, Fourth: %d, Length: %zu\n", first, value_of_fourth, length);
    
    return 0;
}

// CHECK: First: 2, Fourth: 7, Length: 8

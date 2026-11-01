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
//
// Set values:
//
//     foo[2] = 16;
//
// In C, arrays don't store their length! You have to calculate it
// using sizeof(array) / sizeof(array[0]) (total bytes / bytes per element).
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // This "const" is going to cause a problem later.
    const int some_primes[] = { 1, 3, 5, 7, 11, 13, 17, 19 };

    // We want to change the first element to 2.
    some_primes[0] = 2;

    int first = some_primes[0];

    // (Problem 2)
    // Access the fourth element (index 3).
    // Array indices start at zero. Replace the placeholder before running.
    int index_of_fourth = ???;
    int value_of_fourth = some_primes[index_of_fourth];

    // (Problem 3)
    // Calculate the length.
    // sizeof produces size_t; print it with %zu.
    size_t length = 0; // Fix me! Use sizeof!

    printf("First: %d, Fourth: %d, Length: %zu\n", first, value_of_fourth, length);
    
    return 0;
}

// CHECK: First: 2, Fourth: 7, Length: 8

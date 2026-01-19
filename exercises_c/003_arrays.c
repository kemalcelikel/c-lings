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
    // Replace ??? with the correct index.
    int fourth = some_primes[3]; // Fixed this one for them? No, let's break it.
    // actually let's make them fill it in.
    // int fourth = some_primes[???]; // C syntax error if I put ???
    // I'll put a wrong index or a placeholder variable.
    // In the Zig example it was `???`.
    // I will use a placeholder value `-1` and ask them to fix it.
    
    int index_of_fourth = -1; // Fix me!
    int value_of_fourth = some_primes[index_of_fourth];

    // (Problem 3)
    // Calculate the length.
    // unsigned long length = ...;
    // Let's just use int for simplicity in printing, though size_t is correct.
    // I'll use a placeholder 0.
    
    int length = 0; // Fix me! Use sizeof!

    printf("First: %d, Fourth: %d, Length: %d\n", first, value_of_fourth, length);
    
    return 0;
}

// CHECK: First: 2, Fourth: 7, Length: 8

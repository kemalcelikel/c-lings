//
// Let's combine functions and loops.
//
// In C, when you pass an array to a function, you usually
// need to pass its size as well, because the array decays
// into a pointer!
//
//     void foo(int *arr, int size) { ... }
//

#include <stdio.h>

// Forward declarations
void printPowersOfTwo(int *numbers, int size);
int twoToThe(int number);

int main(void) {
    int my_numbers[] = { 5, 6, 7, 8 };

    // Pass the array and its size (4)
    printPowersOfTwo(my_numbers, 4);
    printf("\n");
    return 0;
}

// CHECK: 32 64 128 256

// (Problem 1)
// Fix the return type. This function prints but returns nothing.
int printPowersOfTwo(int *numbers, int size) {
    for (int i = 0; i < size; i++) {
        int n = numbers[i];
        printf("%d ", twoToThe(n));
    }
}

// (Problem 2)
// Implement this function manually using a loop.
int twoToThe(int number) {
    int n = 0;
    int total = 1;

    while (n < number) {
        total *= 2;
        n++; // Don't forget to increment!
    }

    // What should we return?
    return ???;
}

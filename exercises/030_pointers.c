//
// Pointers are variables that store memory addresses.
//
//     int a = 5;
//     int *p = &a; // p points to a
//
//     &a  -> Address of a
//     *p  -> Value at the address p points to (Dereference)
//

#include <stdio.h>

int main(void) {
    int num1 = 5;
    int *num1_pointer = &num1;

    int num2 = 0;

    // (Problem 1)
    // Obtain num2 through num1_pointer, rather than naming num1 directly.
    num2 = ???;

    printf("num1: %d, num2: %d\n", num1, num2);
    return 0;
}

// CHECK: num1: 5, num2: 5

//
// Function pointers allow you to store the address of a function
// and call it later.
//
//     int (*func_ptr)(int, int) = &add;
//     int result = func_ptr(1, 2);
//

#include <stdio.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

int main(void) {
    // (Problem 1)
    // Define a function pointer named 'op' that takes two ints and returns an int.
    // Initialize it to point to 'add'.
    int (*op)(int, int) = ???;

    printf("Add: %d\n", op(10, 5));

    // (Problem 2)
    // Point it to 'sub'.
    op = ???;
    
    printf("Sub: %d\n", op(10, 5));

    return 0;
}

// CHECK: Add: 15
// CHECK: Sub: 5

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
    // The pointer's type is supplied. Select the operation for the first call.
    int (*op)(int, int) = ???;

    printf("Add: %d\n", op(10, 5));

    // (Problem 2)
    // Select the operation for the second call without changing the call itself.
    op = ???;
    
    printf("Sub: %d\n", op(10, 5));

    return 0;
}

// CHECK: Add: 15
// CHECK: Sub: 5

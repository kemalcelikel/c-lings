//
// A common pattern in C to return a value OR an error is to:
// 1. Return an int status code (0 for success, non-zero for error).
// 2. Use a pointer to return the actual value.
//
//     int get_number(int *out_value) {
//         if (something_wrong) return -1; // Error
//         *out_value = 42;
//         return 0; // Success
//     }
//
// &result supplies the address of result; *out_n accesses that integer.
// We will study pointers in more detail in lesson 030.
// This example uses small integers and assumes a valid output pointer.

#include <stdio.h>

// Returns 0 on success, -1 on error.
// Writes the result to *out_n.
int divide(int a, int b, int *out_n) {
    if (b == 0) {
        return -1; // Error: Division by zero
    }
    
    // (Problem 1)
    // Write the result of a / b to the location pointed to by out_n.
    // Remember to dereference the pointer!
    ??? = a / b;
    
    return 0; // Success
}

int main(void) {
    int result;
    int status;

    // Try 10 / 2
    status = divide(10, 2, &result);
    if (status == 0) {
        printf("10 / 2 = %d\n", result);
    } else {
        printf("Error dividing 10 / 2\n");
    }

    // Try 5 / 0
    // (Problem 2)
    // Call divide with 5 and 0.
    status = divide(5, ???, &result);
    
    if (status != 0) {
        printf("Cannot divide by zero!\n");
    }

    return 0;
}

// CHECK: 10 / 2 = 5
// CHECK: Cannot divide by zero!

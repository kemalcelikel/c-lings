//
// Variadic functions can take a variable number of arguments.
// They use the <stdarg.h> header.
// Call va_start(list, last_named_argument), retrieve with va_arg(list, type),
// and always finish with va_end(list). The caller must provide the promised
// count and types; variadic arguments do not carry runtime type information.
//

#include <stdio.h>
#include <stdarg.h>

// This function calculates the sum of 'count' integers.
int sum_all(int count, ...) {
    int total = 0;
    va_list args;
    
    // (Problem 1)
    // Begin traversal of the arguments following the named parameter.
    ???(args, count);

    for (int i = 0; i < count; i++) {
        // (Problem 2)
        // Retrieve the type that this function's callers promise to supply.
        total += va_arg(args, ???);
    }

    // (Problem 3)
    // Finish the traversal before returning.
    ???(args);

    return total;
}

int main(void) {
    int s1 = sum_all(3, 10, 20, 30);
    int s2 = sum_all(5, 1, 2, 3, 4, 5);

    printf("Sum 1: %d\n", s1);
    printf("Sum 2: %d\n", s2);

    return 0;
}

// CHECK: Sum 1: 60
// CHECK: Sum 2: 15

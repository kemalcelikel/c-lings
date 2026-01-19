//
// Variadic functions can take a variable number of arguments.
// They use the <stdarg.h> header.
//

#include <stdio.h>
#include <stdarg.h>

// This function calculates the sum of 'count' integers.
int sum_all(int count, ...) {
    int total = 0;
    va_list args;
    
    // (Problem 1)
    // Initialize the argument list.
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        // (Problem 2)
        // Get the next argument of type int.
        total += va_arg(args, int);
    }

    // (Problem 3)
    // Clean up the argument list.
    va_end(args);

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


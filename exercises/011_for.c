//
// In C, the 'for' loop is the most common way to loop with an increment.
//
//     for (init; condition; increment) {
//         // body
//     }
//
// Example:
//
//     for (int i = 0; i < 10; i++) {
//         // ...
//     }
//

#include <stdio.h>

int main(void) {
    int n;

    // (Problem 1)
    // Rewrite the while loop from the previous exercise as a for loop.
    // Preserve its sequence and final value. Which part controls stopping?
    for (n = 2; ???; n = n * 2) {
        printf("%d ", n);
    }

    printf("n=%d\n", n);
    return 0;
}

// CHECK: n=1024

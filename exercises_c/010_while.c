//
// The 'while' loop in C runs as long as the condition is true (non-zero).
//
//     while (condition) {
//         // do something
//     }
//

#include <stdio.h>

int main(void) {
    int n = 2;

    // (Problem 1)
    // Please use a condition that is true UNTIL "n" reaches 1024.
    while (???) {
        printf("%d ", n);
        n *= 2;
    }

    printf("n=%d\n", n);
    return 0;
}

// CHECK: n=1024

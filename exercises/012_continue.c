//
// The 'continue' statement skips the rest of the current iteration
// and jumps to the next one.
//
//     for (int i = 0; i < 10; i++) {
//         if (i == 5) continue; // Skip 5
//         printf("%d", i);
//     }
//

#include <stdio.h>

int main(void) {
    // Print numbers 1 to 20, but skip those divisible by 3 or 5.
    for (int n = 1; n <= 20; n++) {
        // Use the modulo operator % to check divisibility.
        // Fill in the statements that skip this iteration.
        if (n % 3 == 0) ???;
        if (n % 5 == 0) ???;
        
        printf("%d ", n);
    }
    printf("\n");
    return 0;
}

// CHECK: 1 2 4 7 8 11 13 14 16 17 19

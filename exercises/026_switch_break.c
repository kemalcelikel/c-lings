//
// CRITICAL: In C, switch cases "fall through" if you don't use 'break'!
//
//     switch (1) {
//         case 1: printf("One"); // No break!
//         case 2: printf("Two");
//     }
//     // Output: OneTwo
//

#include <stdio.h>

int main(void) {
    int n = 1;

    printf("Count: ");

    // We want to print "1" if n is 1, but we forgot the break!
    switch (n) {
        case 1:
            printf("1");
            // (Problem 1)
            // Add the missing keyword to stop it from printing "2" as well.
            ???;
        case 2:
            printf("2");
            break;
    }
    printf("\n");
    return 0;
}

// CHECK-EXACT: Count: 1

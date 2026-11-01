//
// After entering a switch case, execution continues through later labels
// unless control leaves that path, for example with break or return.
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

    // Exactly one case's message should be printed for this value.
    switch (n) {
        case 1:
            printf("1");
            // (Problem 1)
            // Finish this case without executing the next case's statements.
            ???;
        case 2:
            printf("2");
            break;
    }
    printf("\n");
    return 0;
}

// CHECK-EXACT: Count: 1

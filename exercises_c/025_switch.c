//
// The 'switch' statement allows you to match a value against constants.
//
//     switch (val) {
//         case 1:
//             // ...
//             break;
//         default:
//             // ...
//     }
//

#include <stdio.h>

int main(void) {
    int lang_chars[] = { 26, 9, 7, 42 };

    for (int i = 0; i < 4; i++) {
        int c = lang_chars[i];
        
        switch (c) {
            case 1: printf("A"); break;
            case 2: printf("B"); break;
            case 7: printf("G"); break;
            case 9: printf("I"); break;
            case 26: printf("Z"); break;
            
            // (Problem 1)
            // Handle all other values with 'default'.
            // Print a question mark "?"
default:
                printf("?");
                break;
        }
    }
    printf("\n");
    return 0;
}

// CHECK: ZIG?

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
    int lang_chars[] = { 3, 42 };

    for (int i = 0; i < 2; i++) {
        int c = lang_chars[i];
        
        switch (c) {
            case 1: printf("A"); break;
            case 2: printf("B"); break;
            case 3: printf("C"); break;
            
            // (Problem 1)
            // Handle all other values with 'default'.
            // Print a question mark "?"
            ???:
                printf("?");
                break;
        }
    }
    printf("\n");
    return 0;
}

// CHECK-EXACT: C?

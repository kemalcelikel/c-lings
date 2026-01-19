//
// C doesn't have built-in error types, but we often use enums
// to define error codes.
//
//     enum Error {
//         SUCCESS,
//         ERROR_NOT_FOUND,
//         ERROR_ACCESS_DENIED
//     };
//

#include <stdio.h>

// Define our error set
typedef enum {
    TOO_BIG,
    TOO_SMALL,
    TOO_FOUR // It's a pun on "Two For"? No, "Too Four" = 4.
} MyNumberError;

// Function prototype
MyNumberError numberFail(int n);

int main(void) {
    int nums[] = { 2, 3, 4, 5, 6 };
    int len = 5;

    for (int i = 0; i < len; i++) {
        int n = nums[i];
        printf("%d", n);

        MyNumberError err = numberFail(n);

        if (err == TOO_BIG) {
            printf(">4. ");
        }
        // (Problem 1)
        // Check if the error is TOO_SMALL
        if (err == ???) {
            printf("<4. ");
        }
        if (err == TOO_FOUR) {
            printf("=4. ");
        }
    }

    printf("\n");
    return 0;
}

// CHECK: 2<4. 3<4. 4=4. 5>4. 6>4.

MyNumberError numberFail(int n) {
    if (n > 4) return TOO_BIG;
    if (n < 4) return TOO_SMALL;
    return TOO_FOUR;
}

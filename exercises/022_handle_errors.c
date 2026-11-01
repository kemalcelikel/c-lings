//
// In C, we handle specific errors by checking the error code.
//
//     int err = do_something();
//     if (err == ERR_NOT_FOUND) {
//         // Handle it
//     } else if (err != SUCCESS) {
//         // Handle other errors
//     }
//
// A switch chooses a matching case label; break exits the switch.
// Example: switch (err) { case SUCCESS: break; case ERR_FAIL: break; }
// We will explore switch further in lesson 025.
//

#include <stdio.h>

typedef enum {
    SUCCESS,
    ERR_TOO_SMALL,
    ERR_TOO_BIG
} MyError;

MyError detectProblems(int n) {
    if (n < 10) return ERR_TOO_SMALL;
    if (n > 20) return ERR_TOO_BIG;
    return SUCCESS;
}

int main(void) {
    int nums[] = { 5, 25, 15 };
    
    for (int i = 0; i < 3; i++) {
        MyError err = detectProblems(nums[i]);
        
        switch (err) {
            case SUCCESS:
                printf("%d is fine.\n", nums[i]);
                break;
            case ERR_TOO_BIG:
                printf("%d is too big!\n", nums[i]);
                break;
            // (Problem 1)
            // Select the status corresponding to this message.
            case ???:
                printf("%d is too small!\n", nums[i]);
                break;
        }
    }
    
    return 0;
}

// CHECK: 5 is too small!
// CHECK: 25 is too big!
// CHECK: 15 is fine.

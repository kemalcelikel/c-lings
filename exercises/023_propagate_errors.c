//
// When a function calls another function that fails, it often needs
// to pass that error up to its caller. This is "bubbling up" the error.
//
//     int do_task() {
//         int err = sub_task();
//         if (err != 0) return err; // Propagate the error
//         return 0;
//     }
//

#include <stdio.h>

typedef enum {
    SUCCESS,
    ERR_FAIL
} Error;

Error step1(void) {
    return SUCCESS;
}

Error step2(void) {
    return ERR_FAIL; // Something went wrong here!
}

Error step3(void) {
    return SUCCESS;
}

Error perform_task(void) {
    Error err;

    err = step1();
    if (err != SUCCESS) return err;

    err = step2();
    // (Problem 1)
    // If step2 failed, we should return the error immediately!
    if (err != SUCCESS) ???;

    err = step3();
    if (err != SUCCESS) return err;

    return SUCCESS;
}

int main(void) {
    Error result = perform_task();
    
    if (result == SUCCESS) {
        printf("Task completed successfully!\n");
    } else {
        printf("Task failed with error %d.\n", result);
    }
    
    return 0;
}

// CHECK: Task failed with error 1.

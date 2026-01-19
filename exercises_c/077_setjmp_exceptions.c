//
// C doesn't have try/catch. But we can simulate it using
// setjmp (save stack context) and longjmp (restore stack context).
//
//     if (setjmp(buf) == 0) {
//         // Try block
//         longjmp(buf, 1); // Throw error 1
//     } else {
//         // Catch block
//     }
//

#include <stdio.h>
#include <setjmp.h>

jmp_buf exception_env;

void risky_function(int x) {
    if (x == 0) {
        printf("Error: x is 0! Throwing exception...\n");
        // (Problem 1)
        // Jump back to the setjmp point.
        // longjmp(buffer, return_value)
        longjmp(exception_env, 100);
    }
    printf("x is %d (fine)\n", x);
}

int main(void) {
    // (Problem 2)
    // Save the current context. 
    // setjmp returns 0 on initial save, and non-zero when longjmp is called.
    int error_code = setjmp(exception_env);

    if (error_code == 0) {
        printf("Try block start.\n");
        risky_function(10);
        risky_function(0); // Will jump!
        printf("This will never print.\n");
    } else {
        printf("Catch block! Caught error: %d\n", error_code);
    }

    return 0;
}

// CHECK: Try block start.
// CHECK: x is 10 (fine)
// CHECK: Error: x is 0! Throwing exception...
// CHECK: Catch block! Caught error: 100

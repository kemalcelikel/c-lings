//
// setjmp and longjmp provide non-local jumps. setjmp establishes a return
// point in an active function; longjmp returns to it from a nested call.
// They do not automatically clean up resources. Never jump to a function
// that has returned. Modified non-volatile local variables in the function
// containing setjmp can have indeterminate values after the jump.
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
        // Return to the context established by main, carrying error 100.
        longjmp(???, 100);
    }
    printf("x is %d (fine)\n", x);
}

int main(void) {
    // (Problem 2)
    // Save the current context. 
    // setjmp returns 0 on initial save, and non-zero when longjmp is called.
    // ISO C restricts where setjmp may appear. Use it directly as a switch
    // controlling expression, not in a variable initializer.
    switch (setjmp(???)) {
    case 0:
        printf("Try block start.\n");
        risky_function(10);
        risky_function(0); // Will jump!
        printf("This will never print.\n");
        break;
    case 100:
        printf("Catch block! Caught error: 100\n");
        break;
    default:
        return 1;
    }

    return 0;
}

// CHECK: Try block start.
// CHECK: x is 10 (fine)
// CHECK: Error: x is 0! Throwing exception...
// CHECK: Catch block! Caught error: 100

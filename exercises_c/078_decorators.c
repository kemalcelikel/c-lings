//
// In Python, decorators wrap functions to add behavior.
// In C, we can write a function that takes a function pointer.
//
//     void wrapper(FuncPtr f, int arg) {
//         log_start();
//         f(arg);
//         log_end();
//     }
//

#include <stdio.h>

typedef int (*Operation)(int, int);

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

// The "Decorator" function
int logged_operation(Operation op, const char* name, int a, int b) {
    printf("--- Calling %s(%d, %d) ---
", name, a, b);
    
    // (Problem 1)
    // Call the passed function.
    int result = op(a, b);
    
    printf("--- Result: %d ---
", result);
    return result;
}

int main(void) {
    // (Problem 2)
    // Wrap the 'add' function.
    logged_operation(add, "ADD", 10, 20);

    // Wrap the 'mul' function.
    logged_operation(mul, "MUL", 5, 5);

    return 0;
}

// CHECK: --- Calling ADD(10, 20) ---
// CHECK: --- Result: 30 ---
// CHECK: --- Calling MUL(5, 5) ---
// CHECK: --- Result: 25 ---


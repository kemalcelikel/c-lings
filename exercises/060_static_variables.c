//
// In C, a 'static' variable inside a function persists its value
// between function calls. It is initialized only once.
//
//     void counter() {
//         static int count = 0;
//         count++;
//         printf("%d\n", count);
//     }
//

#include <stdio.h>

void increment_and_print(void) {
    // (Problem 1)
    // Keep this function-local count across calls rather than starting over.
    int call_count = 0;
    
    call_count++;
    printf("Call count: %d\n", call_count);
}

int main(void) {
    increment_and_print();
    increment_and_print();
    increment_and_print();
    return 0;
}

// CHECK: Call count: 1
// CHECK: Call count: 2
// CHECK: Call count: 3

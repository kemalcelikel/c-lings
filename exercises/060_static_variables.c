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
    // Declare a static integer named 'call_count' initialized to 0.
    int call_count = 0; // Add the storage-class keyword.
    
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

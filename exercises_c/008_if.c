//
// The 'if' statement in C works like this:
//
//     if (condition) {
//         // do something
//     } else {
//         // do something else
//     }
//
// Unlike Zig, C treats 0 as false and non-zero as true.
//
//     if (1) { ... } // True
//     if (0) { ... } // False
//

#include <stdio.h>

int main(void) {
    int foo = 42;

    // (Problem 1)
    // Please check if foo is equal to 42.
    // Remember, use '==' for comparison, not '='!
    if (foo = 42) {
        printf("Foo is 42!\n");
    } else {
        printf("Foo is not 42?\n");
    }
    
    return 0;
}

// CHECK: Foo is 42!


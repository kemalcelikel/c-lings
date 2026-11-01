//
// The 'if' statement in C works like this:
//
//     if (condition) {
//         // do something
//     } else {
//         // do something else
//     }
//
// C treats 0 as false and non-zero as true.
//
//     if (1) { ... } // True
//     if (0) { ... } // False
//
// Assignment (=) stores a value; equality (==) compares two values.
// Conditions can be combined with && (both true), || (either true),
// and ! (logical negation). For example: age >= 18 && has_ticket.
//

#include <stdio.h>

int main(void) {
    int foo = 42;

    // (Problem 1)
    // This branch should test foo without changing it.
    if (foo = 42) {
        printf("Foo is 42!\n");
    } else {
        printf("Foo is not 42?\n");
    }
    
    return 0;
}

// CHECK: Foo is 42!

//
// Functions!
//
// C functions are defined like this:
//
//     int foo(int n) {
//         return n + 1;
//     }
//
// The return type comes first!
//

#include <stdio.h>

// (Problem 1)
// Complete the declaration to agree with the value returned by the function.

??? deepThought(void) {
    return 42;
}

int main(void) {
    int answer = deepThought();
    printf("Answer to the Ultimate Question: %d\n", answer);
    return 0;
}

// CHECK: Answer to the Ultimate Question: 42

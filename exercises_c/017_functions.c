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

// Declare the function prototype if defined after main,
// or just define it before main.
// We'll define it before main.

// (Problem 1)
// Define deepThought() so it returns the integer 42.
// Replace ??? with the correct return type and syntax.

int deepThought(void) {
    return 42;
}

int main(void) {
    int answer = deepThought();
    printf("Answer to the Ultimate Question: %d\n", answer);
    return 0;
}

// CHECK: Answer to the Ultimate Question: 42

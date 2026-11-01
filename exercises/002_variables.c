//
// C has variables that can be modified and variables that are constant.
//
//     int a = 10;
//     a = 20; // OK
//
//     const int b = 30;
//     b = 40; // Error!
//
// Make the program compile while keeping pi constant and preserving its
// initial value. Which statement conflicts with that requirement?
//

#include <stdio.h>

int main(void) {
    int x = 5;
    x = x + 5;

    const int pi = 314159;
    
    // Does this operation agree with the declaration above?
    pi = 3;

    printf("x: %d, pi: %d\n", x, pi);
    return 0;
}

// CHECK: x: 10, pi: 314159

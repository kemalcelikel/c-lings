//
// C has variables that can be modified and variables that are constant.
//
//     int a = 10;
//     a = 20; // OK
//
//     const int b = 30;
//     b = 40; // Error!
//
// Please fix the error below by either removing the 'const' keyword
// or by not changing the value of 'pi'.
//

#include <stdio.h>

int main(void) {
    int x = 5;
    x = x + 5;

    const int pi = 314159;
    
    // Oh no! We are trying to change a constant!
    pi = 3;

    printf("x: %d, pi: %d\n", x, pi);
    return 0;
}

// CHECK: x: 10, pi: 314159


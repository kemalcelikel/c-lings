//
// You can swap two integers without a temporary variable using XOR (^).
//
//     x = x ^ y;
//     y = y ^ x;
//     x = x ^ y;
//

#include <stdio.h>

int main(void) {
    // binary literals are 0b...
    int x = 0b1101; // 13
    int y = 0b1011; // 11

    printf("Before swap: x=%d, y=%d\n", x, y);

    // (Problem 1)
    // Complete the XOR swap.
    x ^= y;
    y ^= x;
    x ^= y; // Corrected line

    printf("After swap:  x=%d, y=%d\n", x, y);

    return 0;
}

// CHECK: Before swap: x=13, y=11
// CHECK: After swap:  x=11, y=13


//
// You can swap two integers without a temporary variable using XOR (^).
//
// XOR has two useful properties: a ^ a is zero, and a ^ 0 is a.
// Combining the two original values lets each be recovered from the other.
//
// This trick requires distinct objects. In ordinary code, prefer a temporary
// variable: it is clearer and also works when references alias the same object.

#include <stdio.h>

int main(void) {
    // Hex literals work in C11; binary literals require C23 or an extension.
    int x = 0x0d; // 13
    int y = 0x0b; // 11

    printf("Before swap: x=%d, y=%d\n", x, y);

    // (Problem 1)
    // Recover the other original value in the final step.
    x ^= y;
    y ^= x;
    x ^= ???;

    printf("After swap:  x=%d, y=%d\n", x, y);

    return 0;
}

// CHECK: Before swap: x=13, y=11
// CHECK: After swap:  x=11, y=13

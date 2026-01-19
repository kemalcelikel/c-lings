//
// Bitwise operators interact with the bits of numbers directly.
//
//     &  AND
//     |  OR
//     ^  XOR
//     ~  NOT
//     << Left Shift
//     >> Right Shift
//

#include <stdio.h>

int main(void) {
    unsigned char a = 0b00001100; // 12
    unsigned char b = 0b00001010; // 10

    // (Problem 1)
    // a & b should be 00001000 (8)
    // a | b should be 00001110 (14)
    // a ^ b should be 00000110 (6)
    
    printf("AND: %d\n", a & b);
    printf("OR:  %d\n", a | b);
    
    // We want 6.
    printf("XOR: %d\n", a ^ b);

    return 0;
}

// CHECK: AND: 8
// CHECK: OR:  14
// CHECK: XOR: 6


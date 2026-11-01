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
    unsigned char a = 0x0c; // 12, binary 00001100
    unsigned char b = 0x0a; // 10, binary 00001010

    // (Problem 1)
    // AND keeps bits set in both operands; OR keeps bits set in either;
    // XOR keeps bits set in exactly one operand.
    
    printf("AND: %d\n", a & b);
    printf("OR:  %d\n", a | b);
    
    // Make this operation agree with its label.
    printf("XOR: %d\n", a | b); // Fix the operator!

    return 0;
}

// CHECK: AND: 8
// CHECK: OR:  14
// CHECK: XOR: 6

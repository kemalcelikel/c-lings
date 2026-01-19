//
// Endianness refers to the order of bytes in memory.
// Little Endian: LSB at lowest address (Intel/AMD).
// Big Endian: MSB at lowest address (Network).
//

#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t num = 0x12345678;
    
    // (Problem 1)
    // Inspect the bytes using a char pointer.
    uint8_t *bytes = (uint8_t*)&num;

    printf("Bytes: %x %x %x %x\n", bytes[0], bytes[1], bytes[2], bytes[3]);

    // If Little Endian: 78 56 34 12
    // If Big Endian:    12 34 56 78
    
    if (bytes[0] == 0x78) {
        printf("System is Little Endian.\n");
    } else if (bytes[0] == 0x12) {
        printf("System is Big Endian.\n");
    } else {
        printf("Unknown endianness (Mixed?).\n");
    }

    return 0;
}

// CHECK: Bytes:
// CHECK: Endian.

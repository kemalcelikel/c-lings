//
// Bitfields allow you to specify how many bits a struct member uses.
// Their layout, ordering, and storage size are implementation-dependent.
// They are not a portable hardware-register or serialization layout.
//

#include <stdio.h>

struct Flags {
    // (Problem 1)
    // Use only 1 bit for these booleans.
    unsigned int is_visible : ???;
    unsigned int has_physics : ???;
    
    // (Problem 2)
    // Use 3 bits for type (values 0-7).
    unsigned int type : ???;
};

int main(void) {
    struct Flags f;
    f.is_visible = 1;
    f.has_physics = 0;
    f.type = 5;

    printf("Size: %zu bytes\n", sizeof(f)); // Likely 4 bytes (int alignment), but uses bits inside.
    printf("Type: %u\n", (unsigned int)f.type);
    
    // Overflowing a bitfield
    unsigned int oversized = f.type + 3; // 8 needs 4 bits.
    f.type = oversized;
    // An unsigned 3-bit field keeps the value modulo 8, giving zero.
    printf("Overflowed Type (assigned 8): %u\n", (unsigned int)f.type);

    return 0;
}

// CHECK: Size:
// CHECK: Type: 5
// CHECK: Overflowed Type (assigned 8): 0

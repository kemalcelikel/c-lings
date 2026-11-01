//
// Bitfields allow you to specify how many bits a struct member uses.
// Their layout, ordering, and storage size are implementation-dependent.
// They are not a portable hardware-register or serialization layout.
//

#include <stdio.h>

struct Flags {
    // (Problem 1)
    // Give each Boolean state the smallest unsigned field that holds 0 and 1.
    unsigned int is_visible : ???;
    unsigned int has_physics : ???;
    
    // (Problem 2)
    // Give type enough bits for values 0 through 7, with no unused high bits.
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

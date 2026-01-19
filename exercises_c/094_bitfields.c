//
// Bitfields allow you to specify how many bits a struct member uses.
// Useful for hardware registers or packing data tightly.
//

#include <stdio.h>

struct Flags {
    // (Problem 1)
    // Use only 1 bit for these booleans.
    unsigned int is_visible : 1;
    unsigned int has_physics : 1;
    
    // (Problem 2)
    // Use 3 bits for type (values 0-7).
    unsigned int type : 3;
};

int main(void) {
    struct Flags f;
    f.is_visible = 1;
    f.has_physics = 0;
    f.type = 5;

    printf("Size: %zu bytes\n", sizeof(f)); // Likely 4 bytes (int alignment), but uses bits inside.
    printf("Type: %d\n", f.type);
    
    // Overflowing a bitfield
    f.type = 8; // 1000 binary (needs 4 bits)
    // Likely becomes 0 or 1 depending on implementation (truncation).
    printf("Overflowed Type (assigned 8): %d\n", f.type);

    return 0;
}

// CHECK: Size: 4 bytes
// CHECK: Type: 5
// CHECK: Overflowed Type (assigned 8): 0

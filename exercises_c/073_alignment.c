//
// Structs are padded by the compiler to align fields in memory.
// This ensures faster access but wastes space.
//
//     struct Normal {
//         char c;  // 1 byte
//         // 3 bytes padding
//         int i;   // 4 bytes
//     }; // Total 8 bytes
//
// We can force packing with `__attribute__((packed))` (GCC/Clang).
//

#include <stdio.h>

struct Normal {
    char c;
    int i;
};

// (Problem 1)
// Add the attribute to pack this struct.
struct __attribute__((packed)) Packed {
    char c;
    int i;
};

int main(void) {
    printf("Size of Normal: %zu\n", sizeof(struct Normal));
    printf("Size of Packed: %zu\n", sizeof(struct Packed));

    // Normal is likely 8. Packed should be 5 (1 + 4).
    if (sizeof(struct Packed) == 5) {
        printf("Packed correctly!\n");
    } else {
        printf("Not packed.\n");
    }

    return 0;
}

// CHECK: Packed correctly!

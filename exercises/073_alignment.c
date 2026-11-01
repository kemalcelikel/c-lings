//
// Structs are padded by the compiler to align fields in memory.
// Padding meets alignment requirements; sizes and requirements vary by ABI.
//
//     struct Normal {
//         char c;  // 1 byte
//         // 3 bytes padding
//         int i;   // 4 bytes
//     }; // Often 8 bytes on Linux, but this is not an ISO C guarantee.
//
// We can force packing with `__attribute__((packed))` (GCC/Clang).
// This is a compiler extension. Packed members may be unaligned; do not pass
// their addresses to code expecting naturally aligned pointers.
//

#include <stdio.h>

struct Normal {
    char c;
    int i;
};

// (Problem 1)
// Request the packed layout for this definition, keeping the ordinary
// definition above unchanged. Consider why this is an explicit choice.
struct ??? Packed {
    char c;
    int i;
};

int main(void) {
    printf("Size of Normal: %zu\n", sizeof(struct Normal));
    printf("Size of Packed: %zu\n", sizeof(struct Packed));

    // Check against the actual member sizes instead of assuming int is 4 bytes.
    if (sizeof(struct Packed) == sizeof(char) + sizeof(int)) {
        printf("Packed correctly!\n");
    } else {
        printf("Not packed.\n");
    }

    return 0;
}

// CHECK: Packed correctly!

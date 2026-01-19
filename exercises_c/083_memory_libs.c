//
// <string.h> also works on raw memory.
//
// memset(ptr, val, size) - Set bytes
// memcpy(dst, src, size) - Copy bytes
// memcmp(p1, p2, size)   - Compare bytes
//

#include <stdio.h>
#include <string.h>

int main(void) {
    int buffer[5];

    // (Problem 1)
    // Initialize the buffer to all 0s using memset.
    // Remember: size is in bytes!
    memset(buffer, 0, sizeof(???));

    // (Problem 2)
    // Copy these values into the buffer using memcpy.
    int values[] = {1, 2, 3, 4, 5};
    memcpy(buffer, values, sizeof(values));

    // (Problem 3)
    // Compare buffer and values.
    if (memcmp(buffer, values, sizeof(values)) == 0) { // Fix expected
        printf("Memory matches!\n");
    }

    return 0;
}

// CHECK: Memory matches!

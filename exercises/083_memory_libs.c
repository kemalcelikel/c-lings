//
// <string.h> also works on raw memory.
//
// memset(ptr, val, size) - Set bytes
// memcpy(dst, src, size) - Copy bytes
// memcmp(p1, p2, size)   - Compare bytes
// memcpy requires non-overlapping regions; use memmove if they overlap.
// memcmp compares representations, not general struct or numeric equality.
//

#include <stdio.h>
#include <string.h>

int main(void) {
    int buffer[5];

    // (Problem 1)
    // Initialize the buffer to all 0s using memset.
    // Remember: size is in bytes!
    memset(buffer, 0, sizeof(???));
    for (int i = 0; i < 5; i++) {
        if (buffer[i] != 0) return 1;
    }

    // (Problem 2)
    // Copy these values into the buffer using memcpy.
    int values[] = {1, 2, 3, 4, 5};
    ???(buffer, values, sizeof(values));

    // (Problem 3)
    // Compare buffer and values.
    if (memcmp(buffer, values, sizeof(values)) == ???) {
        printf("Memory matches!\n");
    }

    return 0;
}

// CHECK: Memory matches!

//
// Sometimes we need the index of the item we are processing.
// In C, since we always loop with an index, this is natural!
//

#include <stdio.h>
#include <math.h> // For pow()

int main(void) {
    // Binary 1101 (little-endian: 1, 0, 1, 1)
    // This means 1*2^0 + 0*2^1 + 1*2^2 + 1*2^3
    int bits[] = { 1, 0, 1, 1 };
    int value = 0;
    int len = 4;

    for (int i = 0; i < len; i++) {
        int bit = bits[i];
        
        // Calculate 2 to the power of i.
        // We can use the shift operator (1 << i) for powers of 2,
        // which is more idiomatic in C than pow().
        // But let's use a placeholder.
        int place_value = (1 << ???); 
        
        value += place_value * bit;
    }

    printf("The value of bits '1101': %d.\n", value);
    return 0;
}

// CHECK: The value of bits '1101': 13.


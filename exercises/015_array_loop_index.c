//
// Sometimes we need the index of the item we are processing.
// An index-based loop makes that position available alongside the value.
// C can also traverse arrays using pointers, which we will study later.
//

#include <stdio.h>

int main(void) {
    // Binary 1101, stored here with the least significant bit first.
    // This means 1*2^0 + 0*2^1 + 1*2^2 + 1*2^3
    int bits[] = { 1, 0, 1, 1 };
    int value = 0;
    int len = 4;

    for (int i = 0; i < len; i++) {
        int bit = bits[i];
        
        // A left shift by k positions multiplies 1 by 2 to the power k.
        // Choose the exponent belonging to this bit's place in the array.
        // These small shift counts stay within the range of int.
        int place_value = (1 << ???); 
        
        value += place_value * bit;
    }

    printf("The value of bits '1101': %d.\n", value);
    return 0;
}

// CHECK: The value of bits '1101': 13.

//
// Functions with parameters.
//

#include <stdio.h>

// (Problem 1)
// Give this function the correct input parameter.
// We want to pass an integer named 'my_number'.
// We will use bit shifting (1 << n) to calculate power of 2.
//
unsigned int twoToThe(int my_number) {
    return 1 << my_number;
}

int main(void) {
    printf("Powers of two: %u %u %u %u\n",
        twoToThe(1),
        twoToThe(2),
        twoToThe(3),
        twoToThe(4)
    );
    return 0;
}

// CHECK: Powers of two: 2 4 8 16


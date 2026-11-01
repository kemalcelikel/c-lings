//
// Functions with parameters.
//

#include <stdio.h>

// (Problem 1)
// Complete the parameter declaration to agree with the body and calls below.
// We use bit shifting (1u << n) for small nonnegative powers of two.
// The shift count must be smaller than the width of unsigned int.
//
unsigned int twoToThe(???) {
    return 1u << my_number;
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

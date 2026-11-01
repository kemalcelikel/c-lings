//
// C performs both implicit and explicit type conversions.
//
// Implicit conversion (Automatic):
//     int a = 10;
//     double b = a; // int to double
//
// Explicit conversion (Casting):
//     double c = 3.14;
//     int d = (int)c; // double to int (truncates)
//
// Warning: Implicitly converting a large type to a smaller one
// can lose data!
//

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h> // PRId32 prints an int32_t portably.

int main(void) {
    int32_t big = 1000;
    
    // (Problem 1)
    // Convert 'big' to uint8_t explicitly.
    // uint8_t only goes up to 255. What happens to 1000?
    uint8_t small = ???;

    printf("Big: %" PRId32 ", Small: %u\n", big, (unsigned int)small);

    // (Problem 2)
    // Calculate average as a float.
    int sum = 10;
    int count = 4;
    
    // In C, int / int results in an int (truncation).
    // We need to cast at least one operand to float.
    float average = sum / count; // Fix the integer division.

    printf("Average: %.1f\n", average);

    return 0;
}

// CHECK: Big: 1000, Small: 232
// CHECK: Average: 2.5

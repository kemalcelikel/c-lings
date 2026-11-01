//
// C has three main floating point types:
//
//     float        (usually 32-bit IEEE 754)
//     double       (usually 64-bit IEEE 754)
//     long double  (extended precision, size varies)
//
// Literals can use scientific notation:
//
//     float f = 1.2e3f; // 1200.0
//
// Floating point math can be imprecise!
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // We want to calculate the weight of the Space Shuttle.
    // 4,480,000 lbs * 0.453592 kg/lb
    //
    // Choose the ordinary floating-point type with more precision than float.
    //
    ??? weight_lbs = 4480000.0;
    ??? conversion_factor = 0.453592;
    
    double weight_kg = weight_lbs * conversion_factor;

    // (Problem 2)
    // Print the computed weight rounded to a whole kilogram.
    printf("Shuttle weight: %f kg\n", weight_kg); // Fix the precision.

    // Rounding can make == surprising; this example's outcome is not checked.
    float a = 0.1f + 0.2f;
    if (a == 0.3f) {
        printf("Equal!\n");
    } else {
        printf("Not equal! a is actually %.10f\n", a);
    }

    return 0;
}

// CHECK: Shuttle weight: 2032092 kg

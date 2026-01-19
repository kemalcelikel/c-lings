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
    // Use 'double' for better precision than 'float'.
    //
    double weight_lbs = 4480000.0;
    double conversion_factor = 0.453592;
    
    double weight_kg = weight_lbs * conversion_factor;

    // (Problem 2)
    // Format the output.
    // %.0f prints with 0 decimal places.
    printf("Shuttle weight: %.0f kg\n", weight_kg);

    // Fun fact: comparing floats with == is dangerous!
    float a = 0.1f + 0.2f;
    if (a == 0.3f) {
        printf("Equal!\n");
    } else {
        printf("Not equal! a is actually %.10f\n", a);
    }

    return 0;
}

// CHECK: Shuttle weight: 2032092 kg

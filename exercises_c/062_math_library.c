//
// The C math library <math.h> provides common mathematical functions.
// Note: You must link with -lm (already handled by check.py).
//

#include <stdio.h>
#include <math.h>

int main(void) {
    double x = 64.0;
    
    // (Problem 1)
    // Calculate the square root of x.
    double root = sqrt(x);

    // (Problem 2)
    // Calculate 2 raised to the power of 10.
    double power = pow(2, 10);

    printf("Sqrt of %.1f is %.1f\n", x, root);
    printf("2^10 is %.1f\n", power);

    // (Problem 3)
    // Round 3.7 to the nearest integer (4.0).
    double rounded = round(3.7);
    printf("3.7 rounded is %.1f\n", rounded);

    return 0;
}

// CHECK: Sqrt of 64.0 is 8.0
// CHECK: 2^10 is 1024.0
// CHECK: 3.7 rounded is 4.0

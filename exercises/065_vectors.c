//
// Modern C compilers (GCC and Clang) have "vector extensions".
// This is a compiler extension, not an ISO C11 feature. This course's GCC
// baseline accepts this attribute under the normal checker flags.
// These allow you to perform SIMD operations using standard operators.
//
//     typedef unsigned char byte8 __attribute__((vector_size(8)));
//
// vector_size takes a byte count, not an element count.
// On the supported platform, each float occupies 4 bytes.
//

#include <stdio.h>

// (Problem 1)
// Define a vector type for 4 floats.
typedef float float4 __attribute__((vector_size(???)));

int main(void) {
    // Initialize vectors
    float4 v1 = { 1.0f, 2.0f, 3.0f, 4.0f };
    float4 v2 = { 5.0f, 6.0f, 7.0f, 8.0f };

    // (Problem 2)
    // Add the two vectors element by element. SIMD instructions may be used;
    // the compiler and target determine the generated machine instructions.
    float4 sum = v1 ??? v2;

    printf("Sum: %.1f %.1f %.1f %.1f\n", sum[0], sum[1], sum[2], sum[3]);

    return 0;
}

// CHECK: Sum: 6.0 8.0 10.0 12.0

//
// Modern C compilers (GCC and Clang) have "vector extensions".
// These allow you to perform SIMD operations using standard operators.
//
//     typedef float float4 __attribute__((vector_size(16)));
//
// This defines a type that holds four floats (4 * 4 bytes = 16 bytes).
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
    // Add the two vectors. This happens in parallel on the CPU!
    float4 sum = v1 ??? v2;

    printf("Sum: %.1f %.1f %.1f %.1f\n", sum[0], sum[1], sum[2], sum[3]);

    return 0;
}

// CHECK: Sum: 6.0 8.0 10.0 12.0


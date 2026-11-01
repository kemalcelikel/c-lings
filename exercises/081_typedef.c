//
// 'typedef' creates a new name for an existing type.
// It helps with readability and portability.
//
//     typedef unsigned long long WideUnsigned; // At least 64 bits.
//     typedef struct Person Person;
//

#include <stdio.h>

// (Problem 1)
// Create a Byte alias for an unsigned single-byte integer type.
typedef ??? Byte;

// (Problem 2)
// Complete the alias for the struct used by main.
typedef struct {
    int x, y;
} ???;

int main(void) {
    Byte b = 255;
    Point p = { .x = 10, .y = 20 };

    printf("Byte: %u\n", (unsigned int)b);
    printf("Point: (%d, %d)\n", p.x, p.y);
    return 0;
}

// CHECK: Byte: 255
// CHECK: Point: (10, 20)

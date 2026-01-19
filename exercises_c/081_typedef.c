//
// 'typedef' creates a new name for an existing type.
// It helps with readability and portability.
//
//     typedef unsigned long long uint64;
//     typedef struct Person Person;
//

#include <stdio.h>

// (Problem 1)
// Create a type alias 'Byte' for 'unsigned char'.
typedef unsigned char Byte;

// (Problem 2)
// Define a struct Point and alias it in one go.
typedef struct {
    int x, y;
} Point;

int main(void) {
    Byte b = 255;
    Point p = { .x = 10, .y = 20 };

    printf("Byte: %u\n", b);
    printf("Point: (%d, %d)\n", p.x, p.y);
    return 0;
}

// CHECK: Byte: 255
// CHECK: Point: (10, 20)

//
// In C, we can hide implementation details using "Opaque Pointers".
// The header file declares `typedef struct Shape Shape;` without defining the struct.
// The user only sees `Shape*` and calls functions like `shape_area(Shape*)`.
// This single-file demonstration shows both sides together. The boundary
// is illustrative: real hiding requires the definition to be in a separate
// translation unit, unavailable to the caller.
//

#include <stdio.h>
#include <stdlib.h>

// --- Public Interface (usually in .h) ---
typedef struct Shape Shape; // Opaque type

Shape* shape_create_square(int side);
int shape_area(Shape* s);
void shape_destroy(Shape* s);

// --- Private Implementation (usually in .c) ---
struct Shape {
    int type; // 0=Square
    int dim;  // side length
};

Shape* shape_create_square(int side) {
    Shape* s = malloc(sizeof(Shape));
    if (s == NULL) return NULL;
    s->type = 0;
    s->dim = side;
    return s;
}

int shape_area(Shape* s) {
    // (Problem 1)
    // Compute the square's area from the implementation's stored dimension.
    return s->dim * ???;
}

void shape_destroy(Shape* s) {
    // (Problem 2)
    // Free the memory.
    free(???);
}

// --- User Code ---
int main(void) {
    Shape* sq = shape_create_square(5);
    if (sq == NULL) return 1;
    
    // printf("%d", sq->dim); // ERROR: Incomplete type (if in different file)
    
    printf("Area: %d\n", shape_area(sq));
    
    shape_destroy(sq);
    return 0;
}

// CHECK: Area: 25

//
// We can write functions using void * and a byte count to handle multiple
// object types. C11 also has _Generic for compile-time type-based selection.
//
//     void swap(void *a, void *b, size_t size);
//

#include <stdio.h>
#include <string.h> // for memcpy
#include <stdlib.h>

// A generic swap function!
// Call with valid, non-overlapping objects of at least size bytes each.
int generic_swap(void *a, void *b, size_t size) {
    if (a == b) return 1;
    // We need a temporary buffer of 'size' bytes.
    void *tmp = malloc(size);
    if (tmp == NULL) return 0;
    
    // memcpy(dest, src, size)
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    // (Problem 1)
    // Copy from tmp to b.
    memcpy(???, ???, size);
    
    free(tmp);
    return 1;
}

int main(void) {
    int i1 = 10, i2 = 20;
    if (!generic_swap(&i1, &i2, sizeof(int))) return 1;
    printf("Ints: %d, %d\n", i1, i2);

    double d1 = 1.5, d2 = 9.9;
    // (Problem 2)
    // Swap the doubles. Don't forget the size!
    if (!generic_swap(&d1, &d2, ???)) return 1;
    printf("Doubles: %.1f, %.1f\n", d1, d2);

    return 0;
}

// CHECK: Ints: 20, 10
// CHECK: Doubles: 9.9, 1.5

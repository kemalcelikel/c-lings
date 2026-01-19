//
// C does not have templates or generics.
// Instead, we often use 'void *' to point to data of any type.
//
//     void swap(void *a, void *b, size_t size);
//

#include <stdio.h>
#include <string.h> // for memcpy
#include <stdlib.h>

// A generic swap function!
void generic_swap(void *a, void *b, size_t size) {
    // We need a temporary buffer of 'size' bytes.
    void *tmp = malloc(size);
    
    // memcpy(dest, src, size)
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    // (Problem 1)
    // Copy from tmp to b.
    memcpy(???, ???, size);
    
    free(tmp);
}

int main(void) {
    int i1 = 10, i2 = 20;
    generic_swap(&i1, &i2, sizeof(int));
    printf("Ints: %d, %d\n", i1, i2);

    double d1 = 1.5, d2 = 9.9;
    // (Problem 2)
    // Swap the doubles. Don't forget the size!
    generic_swap(&d1, &d2, ???);
    printf("Doubles: %.1f, %.1f\n", d1, d2);

    return 0;
}

// CHECK: Ints: 20, 10
// CHECK: Doubles: 9.9, 1.5


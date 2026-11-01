//
// In C, you can allocate memory on the "heap" using malloc().
// This memory persists until you explicitly free it!
//
//     int *p = malloc(sizeof(int));
//     if (p == NULL) return 1; // Allocation can fail.
//     *p = 10;
//     free(p);
//
// If you forget to free, it's a "memory leak".
//

#include <stdio.h>
#include <stdlib.h> // Required for malloc/free

int main(void) {
    // Allocate space for one integer
    int *p = malloc(sizeof(int));

    if (p == NULL) {
        // Malloc can fail!
        return 1;
    }

    *p = 42;
    printf("Value: %d\n", *p);

    // (Problem 1)
    // We are done with the memory. Free it!
    free(???);

    return 0;
}

// CHECK: Value: 42

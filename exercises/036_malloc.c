//
// In C, you can allocate memory on the "heap" using malloc().
// This memory persists until you explicitly free it!
//
//     int *score = malloc(sizeof(int));
//     if (score == NULL) return 1; // Allocation can fail.
//     *score = 10;
//     free(score);
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
    // Release the allocation now that it is no longer needed.
    free(???);

    return 0;
}

// CHECK: Value: 42

//
// Memory safety is critical in C.
// 1. Double Free: Freeing the same pointer twice.
// 2. Dangling Pointer: Using a pointer after freeing it.
// 3. NULL Dereference: Using a NULL pointer.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    *p = 10;

    printf("Value: %d\n", *p);

    free(p);
    // (Problem 1)
    // To prevent dangling pointer bugs, set the pointer to NULL after freeing.
    p = ???;

    // (Problem 2)
    // Check for NULL before using.
    if (p != NULL) {
        // This won't happen now!
        printf("Value: %d\n", *p);
    }

    // Double free protection
    // free(NULL) is safe in C (it does nothing).
    free(p); 

    return 0;
}

// CHECK: Value: 10

//
// Memory safety is critical in C.
// 1. Double free: Releasing an allocation that has already been released.
// 2. Dangling pointer: A pointer whose target's lifetime has ended.
// 3. Null dereference: Attempting to access an object through a null pointer.
// A pointer can be cleared after release, but other aliases are not cleared.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    if (p == NULL) return 1;
    *p = 10;

    printf("Value: %d\n", *p);

    free(p);
    // (Problem 1)
    // Clear this stored address so the later guard and cleanup do not access
    // the released object. No other aliases exist in this example.
    p = ???;

    // The guard is supplied; it relies on p being updated after release.
    if (p != NULL) {
        printf("Value: %d\n", *p);
    }

    // Double free protection
    // free(NULL) is safe in C (it does nothing).
    free(p); 

    return 0;
}

// CHECK: Value: 10

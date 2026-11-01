//
// calloc() is like malloc(), but it initializes the memory to zero.
// It also takes two arguments: number of items, and size of each item.
//
//     int *arr = calloc(3, sizeof(int));
//     // arr[0] is 0, arr[1] is 0, etc.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Obtain storage for five integers that initially contain zero.
    // Do not add a separate initialization loop.
    int *nums = ???;
    
    if (nums == NULL) return 1;

    // Verify they are zero
    for (int i = 0; i < 5; i++) {
        if (nums[i] != 0) {
            printf("Error: Not zero!\n");
            free(nums);
            return 1;
        }
    }
    printf("All zero!\n");

    // (Problem 1)
    // Release the allocation after its last use.
    free(???);

    return 0;
}

// CHECK: All zero!

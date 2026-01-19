//
// calloc() is like malloc(), but it initializes the memory to zero.
// It also takes two arguments: number of items, and size of each item.
//
//     int *arr = calloc(5, sizeof(int));
//     // arr[0] is 0, arr[1] is 0, etc.
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Allocate an array of 5 integers, initialized to 0.
    int *nums = calloc(5, sizeof(int));
    
    if (nums == NULL) return 1;

    // Verify they are zero
    for (int i = 0; i < 5; i++) {
        if (nums[i] != 0) {
            printf("Error: Not zero!\n");
            return 1;
        }
    }
    printf("All zero!\n");

    // (Problem 1)
    // Don't forget to free!
    free(???);

    return 0;
}

// CHECK: All zero!

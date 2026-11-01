//
// realloc() lets you resize a memory block.
//
//     int *arr = malloc(sizeof(int) * 2);
//     // ... fill arr ...
//     int *new_arr = realloc(arr, sizeof(int) * 10);
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(sizeof(int) * 2);
    if (arr == NULL) return 1;
    arr[0] = 10;
    arr[1] = 20;

    // We want to add more numbers! Resize to hold 4 integers.
    // (Problem 1)
    // Use realloc.
    int *new_arr = realloc(arr, sizeof(int) * ???);

    if (new_arr == NULL) {
        free(arr); // realloc didn't free original on failure
        return 1;
    }
    arr = new_arr;

    arr[2] = 30;
    arr[3] = 40;

    printf("Last: %d\n", arr[3]);
    free(arr);
    return 0;
}

// CHECK: Last: 40

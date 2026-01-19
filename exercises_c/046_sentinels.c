//
// A sentinel is a special value that marks the end of a sequence.
// In C, strings are sentineled by '\0' (0).
//
// You can also use sentinels for arrays of other types.
// For example, an array of pointers ending with NULL.
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // Create an array of integers that ends with -1 as a sentinel.
    int nums[] = { 10, 20, 30, 40, -1 };

    // (Problem 2)
    // Loop through the array until you hit the sentinel.
    // Do NOT use a length variable.
    int i = 0;
    while (nums[i] != -1) {
        printf("%d ", nums[i]);
        i++;
    }
    printf("\n");

    // (Problem 3)
    // String length calculation.
    char *str = "Hello";
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    printf("Length: %d\n", len);

    return 0;
}

// CHECK: 10 20 30 40 
// CHECK: Length: 5

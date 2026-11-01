//
// A sentinel is a special value that marks the end of a sequence.
// In C, strings are terminated by '\0' (0).
//
// You can also use sentinels for arrays of other types.
// For example, an array of pointers ending with NULL.
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // Use a negative sentinel that cannot be confused with these positive data.
    // Keep the array and traversal in agreement.
    int nums[] = { 10, 20, 30, 40, ??? };

    // (Problem 2)
    // Loop through the array until you hit the sentinel.
    // Do NOT use a length variable.
    int i = 0;
    while (nums[i] != ???) {
        printf("%d ", nums[i]);
        i++;
    }
    printf("\n");

    // (Problem 3)
    // String length calculation.
    const char *str = "Hello";
    int len = 0;
    while (str[len] != ???) {
        len++;
    }
    printf("Length: %d\n", len);

    return 0;
}

// CHECK: 10 20 30 40 
// CHECK: Length: 5

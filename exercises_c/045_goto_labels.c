//
// C does not have labeled breaks like Zig (break :label).
// To break out of nested loops, we traditionally use 'goto'.
//
//     while (1) {
//         while (1) {
//             if (condition) goto end;
//         }
//     }
//     end:
//     printf("Done!\n");
//

#include <stdio.h>

int main(void) {
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int target = 5;
    int found = 0;

    // (Problem 1)
    // We want to find the target and stop immediately.
    // Use a goto to break out of both loops.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == target) {
                found = 1;
                goto end;
            }
        }
    }

    if (found) {
        printf("Found %d!\n", target);
    }

// Define the label here
end:
    printf("Search finished.\n");

    return 0;
}

// CHECK: Found 5!
// CHECK: Search finished.

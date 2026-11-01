//
// A break exits only the innermost loop. A goto can exit nested loops.
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
    // The transfer must leave both loops and continue with the report.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == target) {
                found = 1;
                goto ???;
            }
        }
    }

// Both successful search and normal loop completion reach this report.
end:
    if (found) {
        printf("Found %d!\n", target);
    }

    printf("Search finished.\n");

    return 0;
}

// CHECK: Found 5!
// CHECK: Search finished.

//
// C has multi-dimensional arrays: arrays whose elements are also arrays.
//
//     int grid[2][3] = {
//         {1, 2, 3},
//         {4, 5, 6}
//     };
//
// You can access elements like grid[row][col].
//

#include <stdio.h>

int main(void) {
    // We have a 2x2 matrix.
    int matrix[2][2] = {
        {1, 2},
        {3, 4}
    };

    // (Problem 1)
    // We want to print the number 4 (row index 1, column index 1).
    // Please fix the indices.
    int x = matrix[0][0]; 

    printf("The value is: %d\n", x);

    return 0;
}

// CHECK: The value is: 4

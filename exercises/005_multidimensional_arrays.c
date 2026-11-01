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
    // Select the matrix element containing the value in the expected output.
    int x = matrix[0][0]; 

    printf("The value is: %d\n", x);

    return 0;
}

// CHECK: The value is: 4

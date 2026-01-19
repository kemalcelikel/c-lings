//
// In C, arrays and pointers are closely related.
// You can do math on pointers!
//
//     int arr[] = {10, 20, 30};
//     int *p = arr; // Points to arr[0]
//
//     p++; // Now points to arr[1]
//     p += 1; // Same thing
//

#include <stdio.h>

int main(void) {
    int nums[] = { 10, 20, 30, 40 };
    int *p = nums; // Point to start
    
    // (Problem 1)
    // We want to print the third element (30).
    // Advance the pointer by 2 positions.
    p += ???;

    printf("Third element: %d\n", *p);
    return 0;
}

// CHECK: Third element: 30


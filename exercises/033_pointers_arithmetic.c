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
// Stay within the same array (or one past its end). Never dereference the
// one-past pointer; arithmetic outside these bounds is undefined behavior.

#include <stdio.h>

int main(void) {
    int nums[] = { 10, 20, 30, 40 };
    int *p = nums; // Point to start
    
    // (Problem 1)
    // We want to print the third element (30).
    // Count the distance from the pointer's current element.
    p += ???;

    printf("Third element: %d\n", *p);
    return 0;
}

// CHECK: Third element: 30

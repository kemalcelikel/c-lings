//
// The keyword 'const' modifies whatever is immediately to its left.
// If there is nothing to the left, it modifies what is to the right.
//
// 1. const int *p  -> Pointer to CONST int (value can't change via p)
// 2. int * const p -> CONST Pointer to int (p can't point elsewhere)
// 3. const int * const p -> CONST Pointer to CONST int
//

#include <stdio.h>

int main(void) {
    int val1 = 10;
    int val2 = 20;

    // A pointer to a constant integer.
    // We cannot change the value it points to, but we can change the pointer.
    const int *p1 = &val1;
    
    // *p1 = 11; // Error!
    p1 = &val2; // OK

    // (Problem 1)
    // Define a constant pointer to val1.
    // You should be able to change *p2, but NOT p2 itself.
    int * const p2 = &val1;
    
    *p2 = 15; // Should be OK
    // p2 = &val2; // Should be Error if correct

    printf("val1 is %d\n", val1);
    
    // (Problem 2)
    // Define a pointer where BOTH are const.
    const int * const p3 = &val2;
    
    printf("p3 points to %d\n", *p3);

    return 0;
}

// CHECK: val1 is 15
// CHECK: p3 points to 20

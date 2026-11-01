//
// In these declarations, const before the * qualifies the pointed-to int;
// const after the * qualifies the pointer itself.
//
// 1. const int *p  -> Pointer to CONST int (value can't change via p)
// 2. int * const p -> CONST Pointer to int (p can't point elsewhere)
// 3. const int * const p -> CONST Pointer to CONST int
//

#include <stdio.h>

int main(void) {
    int val1 = 10;
    int val2 = 20;

    // Read-only access through p1 does not make val1 itself constant.
    const int *p1 = &val1;
    
    // (Problem 1)
    // Make p1 refer to the other integer without changing either integer.
    *p1 = val2;
    printf("p1 points to %d\n", *p1);

    int * const p2 = &val1;
    
    // (Problem 2)
    // Change val1 to 15 through p2 while keeping p2's stored address.
    p2 = 15;

    printf("val1 is %d\n", val1);
    
    // (Problem 3)
    // Both parts of p3 are read-only. Choose its initial target so it reads
    // the value required by the output; do not change either qualification.
    const int * const p3 = ???;
    
    printf("p3 points to %d\n", *p3);

    return 0;
}

// CHECK-EXACT: p1 points to 20
// CHECK-EXACT: val1 is 15
// CHECK-EXACT: p3 points to 20

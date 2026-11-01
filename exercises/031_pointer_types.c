//
// Pointers have types. An `int *` points to an `int`.
// A `char *` points to a `char`.
//
//     char c = 'A';
//     char *pc = &c;
//

#include <stdio.h>

int main(void) {
    char letter = 'C';
    int number = 10;

    // (Problem 1)
    // Complete the declaration to match the object whose address is stored.
    ??? p_letter = &letter;

    // (Problem 2)
    // Do the same for this different object type.
    ??? p_number = &number;

    printf("%c %d\n", *p_letter, *p_number);
    return 0;
}

// CHECK-EXACT: C 10

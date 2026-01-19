//
// Pointers have types. An `int *` points to an `int`.
// A `char *` points to a `char`.
//
//     char c = 'A';
//     char *pc = &c;
//

#include <stdio.h>

int main(void) {
    char letter = 'Z';
    int number = 10;

    // (Problem 1)
    // Declare a pointer to 'letter'.
    char * p_letter = &letter;

    // (Problem 2)
    // Declare a pointer to 'number'.
    int * p_number = &number;

    printf("%c %d\n", *p_letter, *p_number);
    return 0;
}

// CHECK: Z 10

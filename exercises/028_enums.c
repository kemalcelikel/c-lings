//
// Enums allow you to define a set of named integer constants.
//
//     enum Color { RED, GREEN, BLUE };
//
// By default, they start at 0 and increment by 1.
//     RED = 0, GREEN = 1, BLUE = 2
//

#include <stdio.h>

// (Problem 1)
// Define an enum named 'Ops' with values: INC, DEC, POW.
typedef enum {
    INC,
    DEC,
    ???
} Ops;

int main(void) {
    Ops op = POW;
    int val = 5;

    switch (op) {
        case INC: val += 1; break;
        case DEC: val -= 1; break;
        case POW: val *= val; break;
    }

    printf("Result: %d\n", val);
    return 0;
}

// CHECK: Result: 25

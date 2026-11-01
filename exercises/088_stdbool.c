//
// Before C99, we used int for booleans.
// C99 introduced _Bool and <stdbool.h> which defines bool, true, false.
//

#include <stdio.h>
#include <stdbool.h>

int main(void) {
    // (Problem 1)
    // Use the standard Boolean alias supplied by the included header.
    ??? is_valid = true;

    if (is_valid) {
        printf("Valid!\n");
    }

    // (Problem 2)
    // Change the state so the second message is printed.
    is_valid = ???;

    if (!is_valid) {
        printf("Not valid!\n");
    }

    return 0;
}

// CHECK: Valid!
// CHECK: Not valid!

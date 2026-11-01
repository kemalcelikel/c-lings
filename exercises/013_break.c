//
// The 'break' statement exits the loop immediately.
//

#include <stdio.h>

int main(void) {
    int n = 1;

    // End the loop at the value in the output check.
    while (1) {
        if (n == 4) ???;
        n++;
    }

    printf("n=%d\n", n);
    return 0;
}

// CHECK: n=4

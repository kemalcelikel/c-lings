//
// The 'break' statement exits the loop immediately.
//

#include <stdio.h>

int main(void) {
    int n = 1;

    // This loop would go forever if we don't break it!
    while (1) {
        if (n == 4) ???;
        n++;
    }

    printf("n=%d\n", n);
    return 0;
}

// CHECK: n=4

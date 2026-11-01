//
// Sometimes code should be unreachable. If execution reaches it,
// it's a bug. In C, we can use assert(0) from <assert.h>.
// Assertions are disabled when NDEBUG is defined; they are debugging aids,
// not a substitute for validating external input.
//

#include <stdio.h>
#include <assert.h>

int main(void) {
    // Choose mode 1 so the valid path runs. Also complete the assertion below.
    int mode = ???;

    switch (mode) {
        case 1:
            printf("Mode 1\n");
            break;
        case 2:
            printf("Mode 2\n");
            break;
        default:
            // This mode should never happen!
            // (Problem 1)
            // Crash the program with an assertion failure.
            assert(???);
            break;
    }
    return 0;
}

// CHECK-EXACT: Mode 1

//
// assert(condition) from <assert.h> checks an assumption at runtime.
// A false condition terminates the program with an assertion diagnostic.
// An always-false assertion can also mark code that should be unreachable.
// Assertions are disabled when NDEBUG is defined; they are debugging aids,
// not a substitute for validating external input.
//

#include <stdio.h>
#include <assert.h>

int main(void) {
    int mode = 1;

    // The switch supports two modes. Repair this assumption so either
    // supported mode is accepted and unsupported modes are rejected.
    assert(mode == 2);

    switch (mode) {
        case 1:
            printf("Mode 1\n");
            break;
        case 2:
            printf("Mode 2\n");
            break;
        default:
            // This mode should never happen!
            assert(0);
            break;
    }
    return 0;
}

// CHECK-EXACT: Mode 1

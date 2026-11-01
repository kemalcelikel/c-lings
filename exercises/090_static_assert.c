//
// C11 introduced _Static_assert to check conditions at compile time.
// If the condition is false, compilation fails!
// Write _Static_assert(constant_condition, "message"). Avoid asserting
// incidental ABI details unless the program genuinely requires them.
//

#include <stdio.h>

struct Data {
    char a;
    int b;
};

int main(void) {
    // (Problem 1)
    // Assert that int occupies at least one byte, as required by C.
    _Static_assert(???, "Integer size invalid!");

    // (Problem 2)
    // A struct must have space for its members, plus any padding.
    _Static_assert(sizeof(struct Data) >= sizeof(char) + sizeof(int),
                   "Struct cannot hold its members!");

    printf("Compile checks passed.\n");
    return 0;
}

// CHECK: Compile checks passed.

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
    // A supplied example of a guaranteed language property.
    _Static_assert(sizeof(int) >= 1, "Integer size invalid!");

    // Express the minimum space this struct needs for its members without
    // assuming a particular int size or an exact amount of padding.
    _Static_assert(???,
                   "Struct cannot hold its members!");

    printf("Compile checks passed.\n");
    return 0;
}

// CHECK: Compile checks passed.

//
// C11 introduced _Static_assert to check conditions at compile time.
// If the condition is false, compilation fails!
//

#include <stdio.h>

struct Data {
    char a;
    int b;
};

int main(void) {
    // (Problem 1)
    // Assert that sizeof(int) is at least 4 bytes.
    _Static_assert(sizeof(int) >= 4, "Integers too small!");

    // (Problem 2)
    // Assert that struct Data is likely padded (size > 5).
    // Note: This relies on implementation, but usually true.
    _Static_assert(sizeof(struct Data) > 5, "Struct is packed?");

    printf("Compile checks passed.\n");
    return 0;
}

// CHECK: Compile checks passed.


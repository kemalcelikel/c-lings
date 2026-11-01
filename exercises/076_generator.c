//
// A stateful iterator produces values one at a time. In C, we can store its
// position and other state in a struct between calls.
//
//     struct Gen { int state; int current; int max; };
//

#include <stdio.h>

typedef struct {
    int state; // "Instruction Pointer"
    int i;     // Local variable
    int max;   // Argument
} RangeGen;

void range_init(RangeGen *gen, int max) {
    gen->state = 0;
    gen->i = 0;
    gen->max = max;
}

// Returns 1 if valid value, 0 if done.
// Puts value in *out_val.
int range_next(RangeGen *gen, int *out_val) {
    switch (gen->state) {
        case 0:
            gen->i = 0;
            /* fall through */
        case 1:
            if (gen->i < gen->max) {
                *out_val = gen->i;
                gen->i++;
                // (Problem 1)
                // Save state to resume here next time!
                gen->state = ???;
                return 1; // Yield
            }
    }
    // Done
    gen->state = -1;
    return 0;
}

int main(void) {
    RangeGen gen;
    range_init(&gen, 3);

    int val;
    // (Problem 2)
    // Loop while range_next returns true (1).
    while (???) {
        printf("Yielded: %d\n", val);
    }
    return 0;
}

// CHECK: Yielded: 0
// CHECK: Yielded: 1
// CHECK: Yielded: 2

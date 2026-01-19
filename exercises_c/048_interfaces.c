//
// C can simulate "interfaces" or "polymorphism" using function pointers.
// A struct can store pointers to functions that act as its "methods".
//

#include <stdio.h>

// Define a function type
typedef void (*ActionFunc)(void);

struct Tool {
    char *name;
    ActionFunc use; // Function pointer
};

void use_hammer(void) {
    printf("BAM! Hammering nails.\n");
}

void use_wrench(void) {
    printf("TWIST! Turning bolts.\n");
}

int main(void) {
    struct Tool hammer = { .name = "Hammer", .use = use_hammer };
    struct Tool wrench = { .name = "Wrench", .use = use_wrench };

    // We can put them in an array and treat them generically!
    struct Tool *toolbox[] = { &hammer, &wrench };

    for (int i = 0; i < 2; i++) {
        printf("Using %s: ", toolbox[i]->name);
        // (Problem 1)
        // Call the 'use' function through the pointer.
        toolbox[i]->use();
    }

    return 0;
}

// CHECK: Using Hammer: BAM! Hammering nails.
// CHECK: Using Wrench: TWIST! Turning bolts.

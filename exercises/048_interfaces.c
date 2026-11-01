//
// C can simulate "interfaces" or "polymorphism" using function pointers.
// A struct can store pointers to functions that act as its "methods".
// void (*fn)(void) declares a pointer to a function taking no arguments
// and returning void. Assign a function name to it, then call it as fn().
//

#include <stdio.h>

// Define a function type
typedef void (*ActionFunc)(void);

struct Tool {
    const char *name;
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
        // Invoke the current tool's action without selecting by its name.
        ???;
    }

    return 0;
}

// CHECK: Using Hammer: BAM! Hammering nails.
// CHECK: Using Wrench: TWIST! Turning bolts.

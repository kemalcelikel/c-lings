//
// Designated initializers allow you to initialize struct members by name.
// Anonymous structs and unions are useful for nested data.
//

#include <stdio.h>

struct Sprite {
    const char *name;
    // (Problem 1)
    // These two representations should share storage rather than sit side by side.
    // Choose one union representation when writing and reading it.
    // Here we use x and y; the array alternative is not active.
    struct {
        ??? {
            int xy[2];
            struct {
                int x;
                int y;
            };
        };
    } pos;
};

int main(void) {
    // (Problem 2)
    // Complete the initial position to agree with the expected output.
    struct Sprite hero = {
        .name = "Cleo",
        .pos = {
            .x = ???,
            .y = 20
        }
    };

    printf("Hero %s at (%d, %d)\n", hero.name, hero.pos.x, hero.pos.y);

    return 0;
}

// CHECK-EXACT: Hero Cleo at (10, 20)

//
// Designated initializers allow you to initialize struct members by name.
// Anonymous structs and unions are useful for nested data.
//

#include <stdio.h>

struct Sprite {
    const char *name;
    // (Problem 1)
    // Complete the union keyword inside 'pos'.
    // It should have 'int xy[2]' and 'struct { int x, y; }'.
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
    // Initialize the sprite using designated initializers.
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

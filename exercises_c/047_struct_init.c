//
// Designated initializers allow you to initialize struct members by name.
// Anonymous structs and unions are useful for nested data.
//

#include <stdio.h>

struct Sprite {
    char *name;
    // (Problem 1)
    // Create an anonymous union for 'pos'.
    // It should have 'int xy[2]' and 'struct { int x, y; }'.
    // This allows accessing position as .pos.x or .pos.xy[0].
    struct {
        union {
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
        .name = "Ziggy",
        .pos = {
            .x = 10,
            .y = 20
        }
    };

    printf("Hero %s at (%d, %d)\n", hero.name, hero.pos.x, hero.pos.xy[1]);

    return 0;
}

// CHECK: Hero Ziggy at (10, 20)

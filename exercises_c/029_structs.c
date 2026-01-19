//
// Structs let you group related data together.
//
//     struct Point {
//         int x;
//         int y;
//     };
//
// You can declare variables of this type:
//
//     struct Point p;
//     p.x = 10;
//     p.y = 20;
//
// Or initialize them:
//
//     struct Point p = { .x = 10, .y = 20 };
//

#include <stdio.h>

// Define an enum for Role
typedef enum {
    WIZARD,
    THIEF,
    WARRIOR
} Role;

// (Problem 1)
// Define the Character struct.
// It needs:
// - role (type Role)
// - gold (type int)
// - health (type int)
struct Character {
    Role role;
    int gold;
    int health; // Add health
};

int main(void) {
    // Initialize
    struct Character glorp = {
        .role = WIZARD,
        .gold = 20,
        .health = 100
    };

    glorp.gold += 5;
    glorp.health -= 10;

    printf("Health: %d, Gold: %d\n", glorp.health, glorp.gold);
    return 0;
}

// CHECK: Health: 90, Gold: 25

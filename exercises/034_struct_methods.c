//
// C doesn't have "methods" attached to structs like classes in C++ or Java.
// Instead, we pass a pointer to the struct as the first argument.
//
//     void my_struct_method(MyStruct *self, int arg) { ... }
//
// For a pointer p, p->field is shorthand for (*p).field.

#include <stdio.h>

typedef struct {
    int damage;
} HeatRay;

typedef struct {
    int health;
} Alien;

// (Problem 1)
// Complete the parameters to support the body below. The caller's alien
// must reflect changes made here, rather than modifying a local copy.
void zap(???, ???) {
    int dmg = ray->damage;
    if (alien->health < dmg) {
        alien->health = 0;
    } else {
        alien->health -= dmg;
    }
}

int main(void) {
    HeatRay weapon = { .damage = 10 };
    Alien monster = { .health = 25 };

    // Zap it 3 times!
    for (int i = 0; i < 3; i++) {
        // (Problem 2)
        // Supply the weapon and monster in the form zap expects.
        zap(???, ???);
        printf("Alien health: %d\n", monster.health);
    }
    
    return 0;
}

// CHECK: Alien health: 15
// CHECK: Alien health: 5
// CHECK: Alien health: 0

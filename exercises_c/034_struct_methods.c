//
// C doesn't have "methods" attached to structs like classes in C++ or Java.
// Instead, we pass a pointer to the struct as the first argument.
//
//     void my_struct_method(MyStruct *self, int arg) { ... }
//

#include <stdio.h>

typedef struct {
    int damage;
} HeatRay;

typedef struct {
    int health;
} Alien;

// (Problem 1)
// Define the zap function.
// It should take a pointer to HeatRay and a pointer to Alien.
void zap(HeatRay *ray, Alien *alien) {
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
        // Pass the addresses of our objects!
        zap(&weapon, &monster);
        printf("Alien health: %d\n", monster.health);
    }
    
    return 0;
}

// CHECK: Alien health: 15
// CHECK: Alien health: 5
// CHECK: Alien health: 0

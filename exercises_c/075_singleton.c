//
// The Singleton pattern ensures only one instance of a struct exists.
// In C, we often use a static variable inside a function to hold the instance.
//

#include <stdio.h>

typedef struct {
    int id;
    int data;
} Config;

// Get the global singleton instance
Config* get_config(void) {
    // (Problem 1)
    // Define a static variable 'instance'.
    // It will be initialized only once!
    static Config instance = { .id = 1, .data = 0 };
    return &instance;
}

void set_data(int d) {
    Config* c = get_config();
    c->data = d;
}

int main(void) {
    Config* c1 = get_config();
    printf("Initial data: %d\n", c1->data);

    // Modify via a helper function
    set_data(42);

    // Access via a new pointer
    Config* c2 = get_config();
    
    // (Problem 2)
    // Check if c1 and c2 point to the same address.
    if (c1 == c2) {
        printf("Singleton works! Data is now: %d\n", c2->data);
    } else {
        printf("Error: Different instances.\n");
    }

    return 0;
}

// CHECK: Singleton works! Data is now: 42


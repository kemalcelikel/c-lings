//
// Reference counting tracks how many owners share a dynamically allocated
// object. Each retained reference must eventually be released.
// This example is single-threaded and does not handle ownership cycles.
//
//     Object created -> ref_count = 1
//     retain()       -> ref_count++
//     release()      -> ref_count--
//     if ref_count == 0 -> free()
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int ref_count;
} SharedInt;

SharedInt* create_int(int value) {
    SharedInt *obj = malloc(sizeof(SharedInt));
    if (obj == NULL) return NULL;
    obj->value = value;
    obj->ref_count = 1; // Starts with 1 owner
    printf("Created %d (refs: 1)\n", value);
    return obj;
}

void retain(SharedInt *obj) {
    // (Problem 1)
    // Increment the reference count.
    obj->ref_count++;
    printf("Retained %d (refs: %d)\n", obj->value, obj->ref_count);
}

void release(SharedInt *obj) {
    // (Problem 2)
    // Decrement ref_count. If it hits 0, free the object!
    obj->ref_count--;
    printf("Released %d (refs: %d)\n", obj->value, obj->ref_count);

    if (obj->ref_count == 0) {
        printf("Freeing %d!\n", obj->value);
        free(???);
    }
}

int main(void) {
    SharedInt *num = create_int(42);
    if (num == NULL) return 1;
    
    retain(num); // Shared ownership
    
    release(num); // One owner leaves
    
    printf("Still alive: %d\n", num->value);
    
    release(num); // Last owner leaves -> Free
    
    return 0;
}

// CHECK: Created 42 (refs: 1)
// CHECK: Retained 42 (refs: 2)
// CHECK: Released 42 (refs: 1)
// CHECK: Still alive: 42
// CHECK: Released 42 (refs: 0)
// CHECK: Freeing 42!

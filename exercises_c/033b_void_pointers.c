//
// A 'void *' is a generic pointer. It has no type.
// You cannot dereference it directly! You must cast it first.
//
//     void *p = &val;
//     *(int*)p = 10;
//

#include <stdio.h>

void print_value(void *ptr, char type) {
    if (type == 'i') {
        // (Problem 1)
        // Cast ptr to int* and dereference it.
        printf("Int: %d\n", *(int*)ptr);
    } else if (type == 'f') {
        // (Problem 2)
        // Cast ptr to float* and dereference it.
        printf("Float: %.1f\n", *(float*)ptr);
    }
}

int main(void) {
    int i = 42;
    float f = 3.14;

    print_value(&i, 'i');
    print_value(&f, 'f');

    return 0;
}

// CHECK: Int: 42
// CHECK: Float: 3.1

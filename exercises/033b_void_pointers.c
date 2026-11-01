//
// A 'void *' is a generic object pointer, with no pointed-to object type.
// Convert it to the correct pointer type before dereferencing it.
// A cast does not change the stored object; the type must match that object.
//
//     void *p = &val;
//     *(int*)p = 10;
//

#include <stdio.h>

void print_value(void *ptr, char type) {
    if (type == 'i') {
        // (Problem 1)
        // Read the object using the type selected by this branch.
        printf("Int: %d\n", ???);
    } else if (type == 'f') {
        // (Problem 2)
        // Read this different object type without changing its representation.
        printf("Float: %.1f\n", ???);
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

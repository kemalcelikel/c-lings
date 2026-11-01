//
// Unions share the same memory for different fields.
//
//     union Data {
//         int i;
//         float f;
//     };
//
// Since a union does not record which member was last stored,
// we often use a "Tagged Union" - a struct containing an enum and a union.
//
//     struct Value {
//         enum Type type;
//         union Data data;
//     };
//

#include <stdio.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT
} Type;

typedef union {
    int i;
    float f;
} Data;

typedef struct {
    Type type;
    Data data;
} Number;

void print_number(Number n) {
    // (Problem 1)
    // Use the tag to choose the member that was stored in each Number.
    if (n.type == TYPE_INT) {
        printf("Int: %d\n", ???);
    } else if (n.type == TYPE_FLOAT) {
        // Print float with 2 decimal places
        printf("Float: %.2f\n", ???);
    }
}

int main(void) {
    Number n1;
    n1.type = TYPE_INT;
    n1.data.i = 42;

    Number n2;
    n2.type = TYPE_FLOAT;
    n2.data.f = 3.14;

    print_number(n1);
    print_number(n2);
    return 0;
}

// CHECK: Int: 42
// CHECK: Float: 3.14

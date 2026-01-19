//
// C99 allows the last member of a struct to be an array with no size.
// This is a "Flexible Array Member".
// It allows allocating a struct and its data in one malloc block.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int length;
    int data[]; // Flexible array
} Packet;

int main(void) {
    int len = 5;

    // (Problem 1)
    // Allocate memory for the struct + the array.
    // sizeof(Packet) + len * sizeof(int)
    Packet *p = malloc(sizeof(Packet) + len * sizeof(int));
    
    p->length = len;

    for (int i = 0; i < len; i++) {
        p->data[i] = i * 10;
    }

    printf("Last element: %d\n", p->data[len-1]);

    free(p);
    return 0;
}

// CHECK: Last element: 40


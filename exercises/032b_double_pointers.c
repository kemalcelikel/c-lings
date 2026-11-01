//
// A double pointer (pointer to a pointer) allows you to modify
// where a pointer points to!
//
//     int a = 10;
//     int *p = &a;
//     int **pp = &p;
//
//     **pp = 20; // changes a
//
// malloc(sizeof(int)) reserves space for an integer, or returns NULL.
// free releases that space. These functions are covered further in lesson 036.

#include <stdio.h>
#include <stdlib.h>

void allocate_int(int **pp, int value) {
    // (Problem 1)
    // Allocate memory for an integer.
    // *pp refers to the pointer itself (ptr in main).
    *pp = malloc(sizeof(int));
    if (*pp == NULL) return;
    
    // (Problem 2)
    // Dereference again to set the value.
    ??? = value;
}

int main(void) {
    int *ptr = NULL;

    // Pass the address of the pointer!
    allocate_int(&ptr, 42);

    if (ptr != NULL) {
        printf("Allocated value: %d\n", *ptr);
        free(ptr);
    } else {
        printf("Pointer is still NULL!\n");
    }

    return 0;
}

// CHECK: Allocated value: 42

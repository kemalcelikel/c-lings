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
    // The allocation and failure handling are supplied for this pointer task.
    // *pp refers to the pointer itself (ptr in main).
    *pp = malloc(sizeof(int));
    if (*pp == NULL) return;
    
    // Store value in the newly allocated integer through pp.
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

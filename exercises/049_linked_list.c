//
// A linked list is a classic data structure using pointers and structs.
// Each node contains data and a pointer to the next node.
//
//     struct Node {
//         int data;
//         struct Node *next;
//     };
//

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

// (Problem 1)
// Function to add a new node at the beginning.
int push(struct Node **head_ref, int new_data) {
    // 1. Allocate node
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) return 0;
    
    // 2. Put in the data
    new_node->data = new_data;
    
    // 3. Preserve the existing list after the new node.
    new_node->next = ???;
    
    // 4. Publish the new start of the list to the caller.
    (*head_ref) = ???;
    return 1;
}

// (Problem 2)
// Function to free the entire list.
void freeList(struct Node *head) {
    struct Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(???); // Release the finished node without losing the rest.
    }
}

int main(void) {
    struct Node *head = NULL;

    if (!push(&head, 10) || !push(&head, 20) || !push(&head, 30)) {
        freeList(head);
        return 1;
    }

    // Print list
    struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data); 
        current = current->next;
    }
    printf("\n");

    freeList(head);
    return 0;
}

// CHECK: 30 20 10

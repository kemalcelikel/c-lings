//
// C doesn't have a built-in "slice" type like Zig.
// A common pattern in C is to use a struct to group a pointer and a length.
//
//     typedef struct {
//         int *data;
//         size_t len;
//     } IntSlice;
//

#include <stdio.h>

typedef struct {
    char *ptr;
    int len;
} CharSlice;

void print_slice(CharSlice slice) {
    for (int i = 0; i < slice.len; i++) {
        printf("%c ", slice.ptr[i]);
    }
    printf("\n");
}

int main(void) {
    char cards[] = { 'A', '4', 'K', '8', '5', '2', 'Q', 'J' };

    // (Problem 1)
    // Create a slice for the first 4 cards.
    CharSlice hand1 = { .ptr = &cards[0], .len = 4 };

    // (Problem 2)
    // Create a slice for the rest of the cards (starting at index 4).
    CharSlice hand2 = { .ptr = ???, .len = ??? };

    printf("Hand 1: ");
    print_slice(hand1);

    printf("Hand 2: ");
    print_slice(hand2);

    return 0;
}

// CHECK: Hand 1: A 4 K 8 
// CHECK: Hand 2: 5 2 Q J

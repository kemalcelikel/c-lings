//
// A common pattern in C is to group a pointer and a length into a "slice".
// This is a borrowed view: the array must outlive it, and C does not check
// its bounds automatically. The length must fit the underlying array.
//
//     typedef struct {
//         int *data;
//         size_t len;
//     } IntSlice;
//

#include <stdio.h>

typedef struct {
    char *ptr;
    size_t len;
} CharSlice;

void print_slice(CharSlice slice) {
    for (size_t i = 0; i < slice.len; i++) {
        printf("%c ", slice.ptr[i]);
    }
    printf("\n");
}

int main(void) {
    char cards[] = { 'A', '4', 'K', '8', '5', '2', 'Q', 'J' };

    // A supplied view of the first half of the array.
    CharSlice hand1 = { .ptr = &cards[0], .len = 4 };

    // Create a view of the remaining cards without copying their storage.
    // Derive the starting address and count from the original array.
    CharSlice hand2 = { .ptr = ???, .len = ??? };

    printf("Hand 1: ");
    print_slice(hand1);

    printf("Hand 2: ");
    print_slice(hand2);

    return 0;
}

// CHECK: Hand 1: A 4 K 8 
// CHECK: Hand 2: 5 2 Q J

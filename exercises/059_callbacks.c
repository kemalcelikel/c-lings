//
// Callbacks are functions passed as arguments to other functions.
// This is achieved using function pointers.
//

#include <stdio.h>

// A function pointer type that takes an int and returns void
typedef void (*IntCallback)(int);

void print_hex(int n) {
    printf("Hex: 0x%X\n", (unsigned int)n);
}

void print_dec(int n) {
    printf("Dec: %d\n", n);
}

// (Problem 1)
// This function takes an array and a callback.
void process_array(int *arr, int len, IntCallback cb) {
    for (int i = 0; i < len; i++) {
        // Let the caller's chosen operation process this element.
        ???;
    }
}

int main(void) {
    int nums[] = { 10, 20, 30 };
    
    printf("Printing in Decimal:\n");
    process_array(nums, 3, print_dec);

    printf("\nPrinting in Hex:\n");
    // (Problem 2)
    // Choose the operation matching the requested output format.
    process_array(nums, 3, ???);

    return 0;
}

// CHECK: Printing in Decimal:
// CHECK: Dec: 10
// CHECK: Dec: 20
// CHECK: Dec: 30
// CHECK: Printing in Hex:
// CHECK: Hex: 0xA
// CHECK: Hex: 0x14
// CHECK: Hex: 0x1E

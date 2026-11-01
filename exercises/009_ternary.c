//
// C has a "ternary operator" which works like an if-else expression.
//
//     condition ? value_if_true : value_if_false
//
// Example:
//
//     int a = 10;
//     int b = (a > 5) ? 100 : 0; // b becomes 100
//

#include <stdio.h>

int main(void) {
    int discount = 1; // 1 means true in C

    // Please use the ternary operator to set the price.
    // If discount is true (1), price is 17.
    // Otherwise, price is 20.
    
    int price = discount ???;

    printf("Price: $%d\n", price);
    return 0;
}

// CHECK: Price: $17

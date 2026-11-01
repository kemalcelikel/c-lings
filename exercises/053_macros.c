//
// Macros are handled by the C Preprocessor before compilation.
// They are often used for constants or small "functions".
//
//     #define PI 3.14
//     #define SQUARE(x) ((x) * (x))
//
// Warning: Always wrap macro arguments in parentheses!
// Arguments may be evaluated more than once: do not pass side effects such
// as i++ to these macros. An ordinary function is safer for such arguments.
//

#include <stdio.h>

// (Problem 1)
// Complete MAX's expression so it selects the larger operand.
#define MAX(a, b) (???) 

// (Problem 2)
// Complete MIN's expression so it selects the smaller operand.
#define MIN(a, b) (???)

int main(void) {
    int x = 10;
    int y = 20;

    printf("Max of %d and %d is %d\n", x, y, MAX(x, y));
    printf("Min of %d and %d is %d\n", x, y, MIN(x, y));

    // Demonstrating why parentheses are important:
    // If we had #define MULT(a, b) a * b
    // Then MULT(1+1, 2) would be 1+1 * 2 = 3 (Wrong!)
    // But with #define MULT(a, b) ((a) * (b))
    // It is ((1+1) * (2)) = 4 (Right!)
    
    return 0;
}

// CHECK: Max of 10 and 20 is 20
// CHECK: Min of 10 and 20 is 10

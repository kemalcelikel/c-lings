//
// Quiz time! FizzBuzz!
//
// 1. Loop from 1 to 16.
// 2. If divisible by 3, print "Fizz".
// 3. If divisible by 5, print "Buzz".
// 4. If neither, print the number.
//

#include <stdio.h>

int main(void) {
    int stop_at = 16;

    for (int i = 1; i <= stop_at; i++) {
        if (i % 3 == 0) printf("Fizz");
        if (i % 5 == 0) printf("Buzz");
        // "and" in C is "&&", "not" is "!"
        if (!(i % 3 == 0) && !(i % 5 == 0)) {
            printf("%d", i);
        }
        printf(", ");
    }
    printf("\n");
    return 0;
}

// CHECK: 1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14, FizzBuzz, 16,

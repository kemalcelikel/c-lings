//
// A recursive function is a function that calls itself.
// It must have a "base case" to stop the recursion.
//

#include <stdio.h>

// Calculate n! (n factorial)
// n! = n * (n-1) * ... * 1
unsigned long long factorial(int n) {
    // Base case: 0! = 1
    if (n <= 0) return 1;

    // (Problem 1)
    // Recursive call.
    return n * factorial(???);
}

int main(void) {
    int num = 5;
    printf("%d! = %llu\n", num, factorial(num));
    return 0;
}

// CHECK: 5! = 120


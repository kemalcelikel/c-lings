//
// You can change a variable's value through a pointer.
//
//     int a = 10;
//     int *p = &a;
//     *p = 20; // a is now 20!
//

#include <stdio.h>

int main(void) {
    int foo = 5;
    int bar = 10;
    
    // We want a pointer that can point to either foo or bar.
    int *p;

    p = &foo;
    // (Problem 1)
    // Increment the value of foo using p.
    // Be careful with operator precedence! (*p)++ or *p += 1.
    ??? += 1;

    p = &bar;
    // (Problem 2)
    // Increment the value of bar using p.
    ??? += 1;

    printf("foo=%d, bar=%d\n", foo, bar);
    return 0;
}

// CHECK: foo=6, bar=11

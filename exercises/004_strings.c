//
// Strings in C are arrays of characters ending with a special
// null byte '\0'.
//
//     char s1[] = "Hello";
//     const char *s2 = "World"; // Do not modify a string literal.
//
// Single quotes are for single characters: 'H'
// Double quotes are for strings: "Hello"
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // We used single quotes for a string!
    const char *dust = 'stardust';

    // (Problem 2)
    // We want to print the letter 'd' (the 5th character, index 4).
    char d = dust[???];

    // (Problem 3)
    // We are using the wrong format specifier for the character 'd'.
    // %s is for Strings, %c is for Characters.
    printf("String: %s, Char: %s\n", dust, d);

    return 0;
}

// CHECK: String: stardust, Char: d

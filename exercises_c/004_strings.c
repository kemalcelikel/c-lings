//
// Strings in C are arrays of characters ending with a special
// null byte '\0'.
//
//     char s1[] = "Hello";
//     char *s2 = "World";
//
// Single quotes are for single characters: 'H'
// Double quotes are for strings: "Hello"
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // We used single quotes for a string!
    char *ziggy = 'stardust';

    // (Problem 2)
    // We want to print the letter 'd' (the 5th character, index 4).
    char d = ziggy[4];

    // (Problem 3)
    // We are using the wrong format specifier for the character 'd'.
    // %s is for Strings, %c is for Characters.
    printf("String: %s, Char: %c\n", ziggy, d);

    return 0;
}

// CHECK: String: stardust, Char: d

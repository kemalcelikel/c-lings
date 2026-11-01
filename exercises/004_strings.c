//
// Strings in C are arrays of characters ending with a special
// null byte '\0'.
//
//     char s1[] = "Hello";
//     const char *s2 = "World"; // Do not modify a string literal.
//
// Single quotes are for single characters: 'H'
// Double quotes are for strings: "Hello"
// printf's %s conversion prints a string; %c prints a character.
// Array indexing starts at zero, including for character arrays.
// The pointer declaration above is a preview; lesson 030 explains pointers.
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // This value should represent a string, not a character constant.
    const char *dust = 'stardust';

    // (Problem 2)
    // Select the letter 'd' from the string.
    char d = dust[???];

    // (Problem 3)
    // Make each printf conversion agree with the corresponding argument.
    printf("String: %s, Char: %s\n", dust, d);

    return 0;
}

// CHECK: String: stardust, Char: d

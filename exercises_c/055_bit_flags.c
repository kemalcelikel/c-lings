//
// Bit flags allow you to store many boolean states in a single integer.
// To set a bit at position n: `flags |= (1 << n)`
// To check a bit at position n: `flags & (1 << n)`
//

#include <stdio.h>
#include <ctype.h> // for tolower() and isalpha()
#include <string.h>

int is_pangram(const char *str) {
    unsigned int flags = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (isalpha(c)) {
            int bit_pos = tolower(c) - 'a';
            // (Problem 1)
            // Set the bit at bit_pos in the 'flags' variable.
            flags |= (1 << bit_pos);
        }
    }
    
    // (Problem 2)
    // We want to check if all 26 bits are set.
    // That means bits 0 to 25.
    // The value would be (1 << 26) - 1.
    // In hex, that is 0x3FFFFFF.
    return flags == 0x3FFFFFF;
}

int main(void) {
    const char *test1 = "The quick brown fox jumps over the lazy dog";
    const char *test2 = "Hello world";

    printf("Test 1 is pangram: %s\n", is_pangram(test1) ? "YES" : "NO");
    printf("Test 2 is pangram: %s\n", is_pangram(test2) ? "YES" : "NO");

    return 0;
}

// CHECK: Test 1 is pangram: YES
// CHECK: Test 2 is pangram: NO

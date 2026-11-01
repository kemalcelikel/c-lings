//
// Quiz time!
//
// Combine arrays, character indexing, and string termination.
// Use what you learned in the preceding lessons; there is no index key here.
//
// We want to construct the word "C Rules" from the scrambled letters.
//

#include <stdio.h>

int main(void) {
    char letters[] = "ulRes C";
    char result[8]; // 7 chars + null terminator

    // We want "C Rules"
    
    // Build the result from letters, rather than replacing it with a literal.
    result[0] = letters[???];
    result[1] = letters[???];
    result[2] = letters[???];
    result[3] = letters[???];
    result[4] = letters[???];
    result[5] = letters[???];
    result[6] = letters[???];
    result[7] = ???;

    printf("%s\n", result);
    return 0;
}

// CHECK-EXACT: C Rules

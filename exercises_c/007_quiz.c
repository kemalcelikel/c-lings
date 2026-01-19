//
// Quiz time!
//
// Let's practice arrays and indexing.
//
// We want to construct the word "C Rules" from the scrambled letters.
//

#include <stdio.h>

int main(void) {
    char letters[] = "ulRes C";
    // Indexes:
    // u = 0
    // l = 1
    // R = 2
    // e = 3
    // s = 4
    //   = 5
    // C = 6

    char result[8]; // 7 chars + null terminator

    // We want "C Rules"
    
    // C
    result[0] = letters[6];
    
    //  (space)
    result[1] = letters[5];

    // R
    result[2] = letters[???];

    // u
    result[3] = letters[0];

    // l
    result[4] = letters[???];

    // e
    result[5] = letters[3];

    // s
    result[6] = letters[4];

    // Don't forget the null terminator!
    result[7] = '\0';

    printf("%s\n", result);
    return 0;
}

// CHECK: C Rules

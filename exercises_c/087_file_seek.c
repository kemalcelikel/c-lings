//
// You can jump around in a file using fseek.
//
//     fseek(f, offset, origin);
//     origin: SEEK_SET (start), SEEK_CUR (current), SEEK_END (end)
//     ftell(f) returns current position.
//

#include <stdio.h>

int main(void) {
    FILE *f = fopen("seek_test.txt", "w+");
    fprintf(f, "1234567890");

    // (Problem 1)
    // Jump to the 5th byte (index 4) from the beginning.
    fseek(f, 4, ???);
    
    // Should print '5'
    printf("Char: %c\n", fgetc(f));

    // (Problem 2)
    // Go to the end of the file.
    fseek(f, 0, SEEK_END);
    
    // (Problem 3)
    // Get the total size (position).
    long size = ftell(f);
    printf("Size: %ld\n", size);

    fclose(f);
    return 0;
}

// CHECK: Char: 5
// CHECK: Size: 10

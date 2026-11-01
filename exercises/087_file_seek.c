//
// You can jump around in a file using fseek.
//
//     fseek(f, offset, origin);
//     origin: SEEK_SET (start), SEEK_CUR (current), SEEK_END (end)
//     ftell(f) returns current position.
// Use binary mode for byte offsets. On the supported regular-file POSIX
// environment, SEEK_END and ftell give the byte length. Not all streams seek.
//

#include <stdio.h>

int main(void) {
    FILE *f = fopen("seek_test.txt", "wb+");
    if (f == NULL) return 1;
    if (fprintf(f, "1234567890") < 0) {
        fclose(f);
        return 1;
    }

    // (Problem 1)
    // Select the origin that makes this offset relative to the file's start.
    if (fseek(f, 4, ???) != 0) {
        fclose(f);
        return 1;
    }
    
    // Should print '5'
    int ch = fgetc(f);
    if (ch == EOF) {
        fclose(f);
        return 1;
    }
    printf("Char: %c\n", ch);

    // The final-position query is supplied for comparison.
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return 1;
    }
    
    // Get the total size (position).
    long size = ftell(f);
    if (size < 0) {
        fclose(f);
        return 1;
    }
    printf("Size: %ld\n", size);

    return fclose(f) != 0;
}

// CHECK: Char: 5
// CHECK: Size: 10

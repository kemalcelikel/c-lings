//
// Reading files in C uses fopen(), fread()/fgets(), and fclose().
//
//     FILE *f = fopen("file.txt", "r");
//

#include <stdio.h>

int main(void) {
    // We will try to open this file itself!
    FILE *f = fopen("039_files_read.c", "r");

    if (f == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    char buffer[100];
    
    // (Problem 1)
    // Read the first line from the stream opened above.
    if (fgets(buffer, 100, ???) != NULL) {
        printf("First line: %s", buffer);
    }

    // (Problem 2)
    // Release the stream after reading.
    fclose(???);

    return 0;
}

// CHECK: First line: //

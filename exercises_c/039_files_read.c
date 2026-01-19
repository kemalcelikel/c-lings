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
    // Read the first line into buffer.
    // fgets(buffer, size, file_pointer)
    if (fgets(buffer, 100, ???) != NULL) {
        printf("First line: %s", buffer);
    }

    // (Problem 2)
    // Always close files!
    fclose(???);

    return 0;
}

// CHECK: First line: //


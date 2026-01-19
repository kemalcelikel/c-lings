//
// Writing to files is similar, use "w" mode.
//
//     FILE *f = fopen("out.txt", "w");
//     fprintf(f, "Hello file!");
//     fclose(f);
//

#include <stdio.h>

int main(void) {
    FILE *f = fopen("output.txt", "w");
    
    if (f == NULL) return 1;

    // (Problem 1)
    // Write "C is fun" to the file.
    fprintf(f, "C is %s\n", "fun");

    fclose(f);
    
    printf("File written.\n");
    return 0;
}

// CHECK: File written.


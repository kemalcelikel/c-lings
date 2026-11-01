//
// Writing to files is similar, use "w" mode.
//
//     FILE *f = fopen("out.txt", "w");
//     fprintf(f, "Hello file!");
//     fclose(f);
//

#include <stdio.h>
#include <string.h> // strcmp(a, b) returns 0 when strings are equal.

int main(void) {
    FILE *f = fopen("output.txt", "w");
    
    if (f == NULL) return 1;

    // (Problem 1)
    // Write "C is fun" to the file.
    if (fprintf(???, "C is %s\n", "fun") < 0) {
        fclose(f);
        return 1;
    }

    if (fclose(f) != 0) return 1;
    // Read back the data so success means the expected text was written.
    f = fopen("output.txt", "r");
    if (f == NULL) return 1;
    char buffer[32];
    int read_ok = fgets(buffer, sizeof(buffer), f) != NULL;
    int close_ok = fclose(f) == 0;
    if (!read_ok || !close_ok || strcmp(buffer, "C is fun\n") != 0) return 1;
    printf("Contents: %s", buffer);
    
    printf("File written.\n");
    return 0;
}

// CHECK: Contents: C is fun
// CHECK: File written.

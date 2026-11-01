//
// Functions that document errno report errors through that macro (typically
// backed by thread-local storage). Only inspect it after detecting failure.
// 'perror' prints a human-readable error message based on errno.
// In POSIX, fopen sets errno on failure. Error numbers and messages vary;
// compare symbolic codes such as ENOENT, not a hardcoded number or wording.
//

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    // Try to open a file that doesn't exist
    FILE *f = fopen("non_existent_file.txt", "r");

    if (f == NULL) {
        // Preserve the failure's error code before later calls can change it.
        int saved_error = ???;
        // The diagnostic and symbolic-code check are supplied below.
        errno = saved_error;
        perror("File error"); // This diagnostic goes to stderr.
        
        // Report the preserved code independently of the diagnostic's wording.
        printf("Error code: %d\n", saved_error);
        if (saved_error != ENOENT) return 1;
        printf("Missing file detected.\n");
    } else {
        fclose(f);
        return 1;
    }

    return 0;
}

// CHECK: Error code:
// CHECK: Missing file detected.

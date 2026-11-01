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
        // Save errno before another library call might change it.
        int saved_error = ???;
        // (Problem 1)
        // Print the error message with a prefix "File error".
        errno = saved_error;
        perror("File error"); // This diagnostic goes to stderr.
        
        // (Problem 2)
        // You can also access the error code directly.
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

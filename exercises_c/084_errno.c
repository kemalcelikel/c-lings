//
// When system calls fail, they set a global variable 'errno'.
// 'perror' prints a human-readable error message based on errno.
//

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    // Try to open a file that doesn't exist
    FILE *f = fopen("non_existent_file.txt", "r");

    if (f == NULL) {
        // (Problem 1)
        // Print the error message with a prefix "File error".
        perror("File error");
        
        // (Problem 2)
        // You can also access the error code directly.
        printf("Error code: %d\n", ???);
    }

    return 0;
}

// CHECK: File error: No such file or directory
// CHECK: Error code: 2

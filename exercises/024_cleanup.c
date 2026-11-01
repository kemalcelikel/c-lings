//
// To ensure cleanup code runs (like freeing memory or closing files)
// when an error occurs, we often use the 'goto' statement
// jumping to a cleanup label at the end of the function.
//
//     int foo() {
//         open_resource();
//         if (error) goto cleanup;
//         
//         // do work
//
//     cleanup:
//         close_resource();
//         return status;
//     }
//

#include <stdio.h>

int main(void) {
    printf("Opening file...\n");
    // Simulate error
    int error = 1;

    if (error) {
        // (Problem 1)
        // On failure, skip the work but still execute the resource cleanup.
        goto ???;
    }

    printf("Writing to file...\n");

cleanup:
    printf("Closing file.\n");
    return 0;
}

// CHECK-EXACT: Opening file...
// CHECK-EXACT: Closing file.

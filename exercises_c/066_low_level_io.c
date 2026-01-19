//
// In C, printf() is a high-level buffered function.
// For low-level output, you can use the write() system call.
//
//     write(file_descriptor, buffer, length);
//
// File descriptor 1 is standard output (stdout).
//

#include <unistd.h> // For write()
#include <string.h> // For strlen()

int main(void) {
    char *msg = "Hello from low-level C!\n";

    // (Problem 1)
    // Write the message to stdout (1).
    write(???, msg, strlen(msg));

    return 0;
}

// CHECK: Hello from low-level C!


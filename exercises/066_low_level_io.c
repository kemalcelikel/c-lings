//
// In C, printf() is a high-level buffered function.
// For low-level output, you can use the write() system call.
// write and file descriptors are POSIX APIs, not ISO C.
//
//     write(file_descriptor, buffer, length);
//
// File descriptor 1 is standard output (stdout).
//

#include <unistd.h> // For write()
#include <string.h> // For strlen()
#include <errno.h> // EINTR means a signal interrupted the operation.

int main(void) {
    const char *msg = "Hello from low-level C!\n";

    // (Problem 1)
    // Choose the standard-output descriptor for this transfer.
    // write can write fewer bytes than requested. Keep sending the remainder.
    size_t length = strlen(msg);
    size_t sent = 0;
    while (sent < length) {
        ssize_t count = write(???, msg + sent, length - sent);
        if (count < 0 && errno == EINTR) continue;
        if (count <= 0) return 1;
        sent += (size_t)count;
    }

    return 0;
}

// CHECK: Hello from low-level C!

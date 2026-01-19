//
// The 'volatile' keyword tells the compiler that a variable's value
// might change at any time without any action being taken by the code.
// This prevents the compiler from optimizing out "unnecessary" reads.
//
// It is commonly used for variables shared with signal handlers
// or memory-mapped hardware.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// (Problem 1)
// Mark this flag as volatile so the while loop doesn't get optimized
// into an infinite loop by a smart compiler.
volatile int keep_running = 1;

void handle_sigint(int sig) {
    keep_running = 0;
}

int main(void) {
    signal(SIGINT, handle_sigint);

    printf("Looping... Press Ctrl+C to stop (if you can!)\n");

    // We simulate a signal after 1 second for the check script.
    // In a real terminal, you'd press Ctrl+C.
    alarm(1);

    while (keep_running) {
        // Just waiting...
    }

    printf("Stopped safely.\n");

    return 0;
}

// CHECK: Looping...
// CHECK: Stopped safely.

//
// The 'volatile' keyword tells the compiler that a variable's value
// may change through mechanisms outside ordinary execution, such as a
// signal handler. Accesses must be evaluated according to the implementation's
// volatile rules rather than replacing repeated reads with a cached value.
//
// It is commonly used for variables shared with signal handlers
// or memory-mapped hardware.
// volatile does not make operations atomic or synchronize threads.
// This lesson uses POSIX alarm(), which sends SIGALRM, not SIGINT.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// (Problem 1)
// Qualify this signal flag so the waiting loop observes the handler's changes.
??? sig_atomic_t keep_running = 1;

void handle_alarm(int sig) {
    (void)sig;
    keep_running = 0;
}

int main(void) {
    if (signal(SIGALRM, handle_alarm) == SIG_ERR) return 1;

    printf("Looping... Waiting for the alarm signal.\n");

    // We simulate a signal after 1 second for the check script.
    // The handler will assign zero to keep_running.
    alarm(1);

    while (keep_running) {
        // Just waiting...
    }

    printf("Stopped safely.\n");

    return 0;
}

// CHECK: Looping...
// CHECK: Stopped safely.

//
// Signals are a way for the operating system to notify a process
// of an event (e.g., user pressed Ctrl+C).
//
// We use <signal.h> to handle them.
//

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// This flag will be set when we receive a signal.
// volatile sig_atomic_t is the safe type for signal flags.
volatile sig_atomic_t stop = 0;

void handle_interrupt(int sig) {
    (void)sig; // suppress unused warning
    stop = 1;
}

int main(void) {
    // (Problem 1)
    // Register the handler for SIGINT (Ctrl+C).
    // signal(SIGNAL_TYPE, handler_function)
    signal(SIGINT, handle_interrupt);

    printf("Running... (Wait, we will simulate a signal in this exercise)\n");
    
    // In a real program, we would loop.
    // For this exercise, we'll just trigger it manually.
    raise(SIGINT);

    if (stop) {
        printf("Received interrupt signal!\n");
    } else {
        printf("Signal not received.\n");
        return 1;
    }

    return 0;
}

// CHECK: Received interrupt signal!

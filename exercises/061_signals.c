//
// Signals are a way for the operating system to notify a process
// of an event (e.g., user pressed Ctrl+C).
//
// We use <signal.h> to handle them.
// signal(signal_number, function) installs a handler and returns SIG_ERR
// if registration fails. raise(signal_number) sends a signal to this program.
//

#include <stdio.h>
#include <signal.h>

// This flag will be set when we receive a signal.
// Use volatile sig_atomic_t for a flag assigned by a signal handler.
// Do not call printf or allocation functions in this handler.
volatile sig_atomic_t stop = 0;

void handle_interrupt(int sig) {
    (void)sig; // suppress unused warning
    stop = 1;
}

int main(void) {
    // (Problem 1)
    // Select the handler that records the interrupt for main to observe.
    if (signal(SIGINT, ???) == SIG_ERR) return 1;

    printf("Running... (Wait, we will simulate a signal in this exercise)\n");
    
    // In a real program, we would loop.
    // For this exercise, we'll just trigger it manually.
    if (raise(SIGINT) != 0) return 1;

    if (stop) {
        printf("Received interrupt signal!\n");
    } else {
        printf("Signal not received.\n");
        return 1;
    }

    return 0;
}

// CHECK: Received interrupt signal!

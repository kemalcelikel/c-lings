//
// C11 introduced optional atomic types in <stdatomic.h>.
// Operations on these are thread-safe without mutexes.
//

#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

// (Problem 1)
// Define an atomic integer.
atomic_int counter = 0;

void* increment(void* arg) {
    for (int i = 0; i < 1000; i++) {
        // (Problem 2)
        // Atomically increment.
        // equivalent to counter++ but thread-safe.
        atomic_fetch_add(&counter, 1);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Should be 2000
    printf("Counter: %d\n", counter);
    return 0;
}

// CHECK: Counter: 2000


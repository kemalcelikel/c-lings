//
// C11 introduced optional atomic types in <stdatomic.h>.
// Atomic operations avoid data races on the atomic object. They need not be
// lock-free, and do not make a sequence of separate operations indivisible.
// The threads in this example use POSIX pthreads; the atomics are ISO C11.
// atomic_int is an atomic integer type. atomic_fetch_add(object, amount)
// performs one atomic read-modify-write operation and returns the old value.
//

#include <stdio.h>
#include <stdatomic.h>
#include <pthread.h>

// (Problem 1)
// Choose a type that permits concurrent updates without a data race.
??? counter = 0;

void* increment(void* arg) {
    (void)arg;
    for (int i = 0; i < 1000; i++) {
        // (Problem 2)
        // Add to the shared object in one atomic read-modify-write operation.
        ???(&counter, 1);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, increment, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, increment, NULL) != 0) {
        pthread_join(t1, NULL);
        return 1;
    }
    int result1 = pthread_join(t1, NULL);
    int result2 = pthread_join(t2, NULL);
    if (result1 != 0 || result2 != 0) return 1;

    // Should be 2000
    printf("Counter: %d\n", counter);
    return 0;
}

// CHECK: Counter: 2000

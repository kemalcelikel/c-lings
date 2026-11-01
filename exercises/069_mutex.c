//
// In multi-threaded programs, we must prevent multiple threads from
// accessing shared resources simultaneously. We use Mutexes (Mutual Exclusions).
// pthread mutexes are POSIX APIs, not ISO C. volatile cannot replace a mutex.
//
//     pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//     pthread_mutex_lock(&lock);
//     // Critical section
//     pthread_mutex_unlock(&lock);
//

#include <stdio.h>
#include <pthread.h>

// A shared counter
int counter = 0;

// (Problem 1)
// Define the mutex.
pthread_mutex_t lock = ???;

void* count_up(void* arg) {
    (void)arg;
    for (int i = 0; i < 10000; i++) {
        // (Problem 2)
        // Lock the mutex before accessing 'counter'.
        ???(&lock);
        
        counter++;
        
        // (Problem 3)
        // Unlock it immediately after!
        ???(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    
    if (pthread_create(&t1, NULL, count_up, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, count_up, NULL) != 0) {
        pthread_join(t1, NULL);
        return 1;
    }
    
    int result1 = pthread_join(t1, NULL);
    int result2 = pthread_join(t2, NULL);
    if (result1 != 0 || result2 != 0) return 1;
    if (pthread_mutex_destroy(&lock) != 0) return 1;
    
    printf("Final counter: %d (Expected: 20000)\n", counter);
    return 0;
}

// CHECK: Final counter: 20000

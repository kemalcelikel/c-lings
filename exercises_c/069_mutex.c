//
// In multi-threaded programs, we must prevent multiple threads from
// accessing shared resources simultaneously. We use Mutexes (Mutual Exclusions).
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
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* count_up(void* arg) {
    for (int i = 0; i < 10000; i++) {
        // (Problem 2)
        // Lock the mutex before accessing 'counter'.
        pthread_mutex_lock(&lock);
        
        counter++;
        
        // (Problem 3)
        // Unlock it immediately after!
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, count_up, NULL);
    pthread_create(&t2, NULL, count_up, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Final counter: %d (Expected: 20000)\n", counter);
    return 0;
}

// CHECK: Final counter: 20000


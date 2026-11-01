//
// POSIX condition variables let threads wait for a shared predicate to change.
// They are always used with a mutex.
// pthread_cond_wait releases the mutex while waiting and reacquires it before
// returning. Always recheck the predicate in a loop: wakeups may be spurious.
//

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;
int waiting = 0;

void* waiter(void* arg) {
    (void)arg;
    pthread_mutex_lock(&lock);
    waiting = 1;
    printf("Waiting...\n");
    pthread_cond_signal(&cond); // Tell the signaler that the waiter started.
    
    // (Problem 1)
    // Wait until 'ready' is true.
    // pthread_cond_wait(cond, mutex)
    while (!ready) {
        ???(&cond, &lock);
    }
    
    printf("Signal received!\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* signaler(void* arg) {
    (void)arg;
    pthread_mutex_lock(&lock);
    // A predicate handshake makes this independent of scheduling or sleeps.
    while (!waiting) pthread_cond_wait(&cond, &lock);
    ready = 1;
    printf("Signaling...\n");
    
    // (Problem 2)
    // Signal the waiting thread.
    ???(&cond);
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, waiter, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, signaler, NULL) != 0) {
        pthread_mutex_lock(&lock);
        ready = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        pthread_join(t1, NULL);
        return 1;
    }
    int result1 = pthread_join(t1, NULL);
    int result2 = pthread_join(t2, NULL);
    if (result1 != 0 || result2 != 0) return 1;
    if (pthread_cond_destroy(&cond) != 0) return 1;
    if (pthread_mutex_destroy(&lock) != 0) return 1;
    return 0;
}

// CHECK: Waiting...
// CHECK: Signaling...
// CHECK: Signal received!

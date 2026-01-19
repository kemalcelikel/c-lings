//
// Condition variables allow threads to wait for a signal.
// They are always used with a mutex.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void* waiter(void* arg) {
    pthread_mutex_lock(&lock);
    
    // (Problem 1)
    // Wait until 'ready' is true.
    // pthread_cond_wait(cond, mutex)
    while (!ready) {
        printf("Waiting...\n");
        pthread_cond_wait(&cond, &lock);
    }
    
    printf("Signal received!\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* signaler(void* arg) {
    sleep(1);
    pthread_mutex_lock(&lock);
    ready = 1;
    printf("Signaling...\n");
    
    // (Problem 2)
    // Signal the waiting thread.
    pthread_cond_signal(&cond);
    
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, waiter, NULL);
    pthread_create(&t2, NULL, signaler, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

// CHECK: Waiting...
// CHECK: Signaling...
// CHECK: Signal received!


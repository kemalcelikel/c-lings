//
// POSIX threads (pthreads) allow for multi-threading in C.
// You must link with -lpthread.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// This function will be executed by threads.
// It must return void* and take void*.
void* thread_func(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d starting...\n", id);
    sleep(1);
    printf("Thread %d finished.\n", id);
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    // (Problem 1)
    // Create the first thread.
    // pthread_create(thread_ptr, attributes, function, argument)
    pthread_create(&thread1, NULL, ???, &id1);

    // Create the second thread.
    pthread_create(&thread2, NULL, thread_func, &id2);

    // (Problem 2)
    // Wait for the threads to finish.
    pthread_join(thread1, NULL);
    pthread_join(???, NULL);

    printf("All threads joined.\n");
    return 0;
}

// CHECK: Thread 1 starting...
// CHECK: Thread 2 starting...
// CHECK: All threads joined.

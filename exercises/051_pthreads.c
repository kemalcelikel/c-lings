//
// POSIX threads (pthreads) allow for multi-threading in C.
// This is POSIX, not ISO C. Compile and link with -pthread.
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
    // Select the entry function that will receive the thread's argument.
    if (pthread_create(&thread1, NULL, ???, &id1) != 0) return 1;

    // Create the second thread.
    if (pthread_create(&thread2, NULL, thread_func, &id2) != 0) {
        pthread_join(thread1, NULL);
        return 1;
    }

    // (Problem 2)
    // Wait for the threads to finish.
    int result1 = pthread_join(thread1, NULL);
    int result2 = pthread_join(???, NULL);
    if (result1 != 0 || result2 != 0) return 1;

    printf("All threads joined.\n");
    return 0;
}

// Threads can print in either order.
// CHECK-ANY: Thread 1 starting...
// CHECK-ANY: Thread 2 starting...
// CHECK-ANY: Thread 1 finished.
// CHECK-ANY: Thread 2 finished.
// CHECK: All threads joined.

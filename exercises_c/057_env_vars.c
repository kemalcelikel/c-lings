//
// Environment variables can be accessed using getenv().
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // (Problem 1)
    // Get the "USER" or "USERNAME" environment variable.
    // Note: This might vary between Linux and Windows. 
    // On Linux it is usually "USER".
    char *user = getenv(???);

    if (user != NULL) {
        printf("Hello, %s!\n", user);
    } else {
        printf("User not found in environment.\n");
    }

    return 0;
}

// CHECK: Hello,

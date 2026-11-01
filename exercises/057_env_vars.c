//
// Environment variables can be accessed using getenv().
//

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // (Problem 1)
    // Read the conventional Linux login-name variable, USER.
    // Environment variables may be absent, so keep the guest fallback.
    char *user = getenv(???);

    if (user != NULL) {
        printf("Hello, %s!\n", user);
    } else {
        printf("Hello, guest!\n");
    }

    return 0;
}

// CHECK: Hello,

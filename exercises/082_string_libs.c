//
// The C Standard Library provides string handling in <string.h>.
//
// strlen(s)    - Length (excluding null terminator)
// strcpy(dst, src) - Copy string
// strcat(dst, src) - Concatenate string
// strcmp(s1, s2) - Compare strings (0 if equal)
// strcpy and strcat require enough destination space, including the null
// terminator, and non-overlapping buffers. Here 50 bytes is ample for 12 bytes.
//

#include <stdio.h>
#include <string.h>

int main(void) {
    char dest[50] = "Hello";
    char src[] = " World";

    // (Problem 1)
    // Append src to dest.
    ???(dest, src);
    printf("Concat: %s\n", dest);

    // (Problem 2)
    // Check if dest is now "Hello World".
    if (strcmp(dest, "Hello World") == ???) {
        printf("Match!\n");
    } else {
        printf("No match.\n");
    }

    // (Problem 3)
    // Print the length.
    printf("Length: %zu\n", ???);

    return 0;
}

// CHECK: Concat: Hello World
// CHECK: Match!
// CHECK: Length: 11

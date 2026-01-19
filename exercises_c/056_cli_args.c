//
// Command line arguments are passed to main() via argc and argv.
//
//     int main(int argc, char *argv[])
//
// argc: Number of arguments (including the program name).
// argv: Array of strings.
//

#include <stdio.h>

int main(int argc, char *argv[]) {
    // (Problem 1)
    // Print the number of arguments passed.
    printf("Arguments count: %d\n", ???);

    // (Problem 2)
    // Loop through all arguments and print them.
    for (int i = 0; i < ???; i++) {
        printf("Argument %d: %s\n", i, argv[???]);
    }

    return 0;
}

// CHECK: Arguments count: 1
// CHECK: Argument 0: ./056_cli_args.out


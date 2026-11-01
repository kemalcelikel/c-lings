//
// Command line arguments are passed to main() via argc and argv.
//
//     int main(int argc, char *argv[])
//
// argc: Number of arguments (including the program name).
// argv: Array of strings.
// The checker launches this program without extra arguments. You can also
// compile and run it yourself with arguments to explore the loop's behavior.
//

#include <stdio.h>

int main(int argc, char *argv[]) {
    // (Problem 1)
    // Report how many entries the argument array contains.
    printf("Arguments count: %d\n", ???);

    // (Problem 2)
    // Visit each argument in order, staying within the supplied count.
    for (int i = 0; i < ???; i++) {
        printf("Argument %d: %s\n", i, argv[???]);
    }

    return 0;
}

// CHECK: Arguments count: 1
// CHECK: Argument 0: ./056_cli_args.out

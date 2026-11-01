//
// Oh no, this is supposed to print "Hello world!" but it needs
// your help.
//
// In C, the main function is the entry point of the program.
// It returns an integer (int) indicating success or failure.
//
//     int main(void) {
//         return 0;
//     }
//
// To print to the console, we usually use the `printf` function.
// Its declaration is provided by the standard input/output header.
// A header tells the compiler about functions supplied elsewhere.
//
//     #include <header_name.h>
//
// Read the compiler diagnostic to find which header this program needs.
//

int main(void) {
    printf("Hello world!\n");
    return 0;
}

// CHECK: Hello world!

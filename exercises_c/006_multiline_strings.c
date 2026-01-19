//
// C allows you to split string literals across multiple lines.
// The compiler will automatically join them!
//
//     char *text = "This is the first line.\n"
//                  "This is the second line.";
//
// Note: You still need explicit '\n' for newlines.
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // Make this program print some lyrics by fixing the syntax error.
    // We forgot the quotes on the second and third lines!
    char *lyrics = "Ziggy played guitar\n"
                   "Jamming good with Andrew Kelley\n"
                   "And the Spiders from Mars\n";

    printf("%s\n", lyrics);
    return 0;
}

// CHECK: Ziggy played guitar
// CHECK: Jamming good with Andrew Kelley
// CHECK: And the Spiders from Mars


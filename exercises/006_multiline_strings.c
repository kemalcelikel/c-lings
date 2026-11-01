//
// C allows you to split string literals across multiple lines.
// The compiler will automatically join them!
//
//     const char *text = "This is the first line.\n"
//                        "This is the second line.";
//
// Note: You still need explicit '\n' for newlines.
//

#include <stdio.h>

int main(void) {
    // (Problem 1)
    // Join these three lines using adjacent string literals.
    // Replace the placeholder with "One line at a time.\n".
    const char *text = "Learning C\n"
                       ???
                       "Keep practicing!\n";

    printf("%s", text);
    return 0;
}

// CHECK-EXACT: Learning C
// CHECK-EXACT: One line at a time.
// CHECK-EXACT: Keep practicing!

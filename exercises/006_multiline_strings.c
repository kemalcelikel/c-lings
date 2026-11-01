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
    // Complete the text so all three output lines match the checks below.
    // Pay attention to where each output line ends.
    const char *text = "Learning C\n"
                       ???
                       "Keep practicing!\n";

    printf("%s", text);
    return 0;
}

// CHECK-EXACT: Learning C
// CHECK-EXACT: One line at a time.
// CHECK-EXACT: Keep practicing!

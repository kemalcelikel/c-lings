//
// C provides several ways to write integer literals:
//
//     int d = 65;          // decimal
//     int h = 0x41;        // hexadecimal
//     int o = 0101;        // octal (starts with 0!)
//     int b = 0b1000001;   // binary (C23 standard, or extension)
//     char c = 'A';        // character literal
//
// Modern C often uses <stdint.h> for fixed-width types:
//
//     uint8_t, int16_t, uint32_t, int64_t
//
// Binary literals are not ISO C11: use decimal, octal, or hex here.
// Exact-width types exist when the platform supports that width. This
// lesson assumes 8-bit bytes and an ASCII-compatible execution character set.
// Please fix the program to print "C is cool."
//

#include <stdio.h>
#include <stdint.h>

int main(void) {
    // We want the characters 'C', ' ', 'i', 's'
    // 'C' is 67 decimal
    // ' ' is 32 decimal
    // 'i' is 105 decimal
    // 's' is 115 decimal
    
    uint8_t msg[] = {
        0x43,       // 'C' in hex
        0x20,       // space in hex (binary 00100000)
        0151,       // 'i' in octal (Careful: 0151 octal = 105 decimal)
        0           // Replace this through the assignment below.
    };

    // (Problem 1)
    // Set the last character to 's' using a hex literal.
    // 's' is 115 decimal (0x73).
    msg[3] = ???;

    printf("%c%c%c%c cool.\n", msg[0], msg[1], msg[2], msg[3]);

    return 0;
}

// CHECK: C is cool.

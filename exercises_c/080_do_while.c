//
// The 'do-while' loop checks the condition AFTER the block.
// It always runs at least once.
//
//     do {
//         // ...
//     } while (condition);
//

#include <stdio.h>

int main(void) {
    int input;

    // (Problem 1)
    // We want to simulate reading input until a valid number (e.g. 5) is found.
    // In this simulation, we'll increment a variable.
    
    int simulator = 0;

    do {
        printf("Checking simulator: %d\n", simulator);
        simulator++;
        
        // (Problem 2)
        // Stop when simulator is 5.
    } while (???);

    printf("Done!\n");
    return 0;
}

// CHECK: Checking simulator: 0
// CHECK: Checking simulator: 4
// CHECK: Done!


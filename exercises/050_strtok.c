//
// C provides 'strtok' in <string.h> for tokenizing strings.
// Warning: strtok modifies the original string and is not thread-safe!
// The first call supplies the string to split. Later calls pass NULL in
// its place to continue that same traversal. The delimiter string lists
// individual separator characters, not a multi-character separator.
//

#include <stdio.h>
#include <string.h>

int main(void) {
    char poem[] = "My name is Ozymandias, King of Kings;\n" 
                  "Look on my Works, ye Mighty, and despair!";

    // The separators for this poem are supplied.
    const char *delims = " ,;\n";
    
    // (Problem 1) Start tokenizing the poem with the chosen separators.
    char *token = strtok(poem, ???);

    int count = 0;
    while (token != NULL) {
        count++;
        printf("%s\n", token);
        
        // (Problem 2)
        // Continue this traversal rather than restarting at the first word.
        token = strtok(???, delims);
    }

    printf("Word count: %d\n", count);
    return 0;
}

// CHECK: My
// CHECK: name
// CHECK: despair!
// CHECK: Word count: 15

//
// C provides 'strtok' in <string.h> for tokenizing strings.
// Warning: strtok modifies the original string and is not thread-safe!
//

#include <stdio.h>
#include <string.h>

int main(void) {
    char poem[] = "My name is Ozymandias, King of Kings;\n" 
                  "Look on my Works, ye Mighty, and despair!";

    // (Problem 1)
    // Specify the delimiters: space, comma, semicolon, newline.
    const char *delims = " ,;\n";
    
    // Get the first token
    char *token = strtok(poem, ???);

    int count = 0;
    while (token != NULL) {
        count++;
        printf("%s\n", token);
        
        // (Problem 2)
        // To get the next token, call strtok with NULL as the first argument.
        token = strtok(???, delims);
    }

    printf("Word count: %d\n", count);
    return 0;
}

// CHECK: My
// CHECK: name
// CHECK: despair!
// CHECK: Word count: 15

//
// C doesn't have a "for each" loop like some other languages.
// Instead, we iterate using an index.
//

#include <stdio.h>

int main(void) {
    char story[] = "hhsnh";
    // We want to loop through this array.
    // But how long is it? sizeof(story) gives 6 (including \0).
    // We can use strlen() from <string.h>, or just know it's 5 chars.
    int len = 5;

    printf("A Dramatic Story: ");

    for (int i = 0; i < len; i++) {
        char scene = story[???]; // Access the element at index i
        
        if (scene == 'h') printf(":-)  ");
        if (scene == 's') printf(":-(  ");
        if (scene == 'n') printf(":-|  ");
    }

    printf("The End.\n");
    return 0;
}

// CHECK: A Dramatic Story: :-)  :-)  :-(  :-|  :-)  The End.

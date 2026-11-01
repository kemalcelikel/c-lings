//
// C doesn't have a "for each" loop like some other languages.
// Instead, we iterate using an index.
//

#include <stdio.h>

int main(void) {
    char story[] = "hhsnh";
    // The terminator is not a scene. This fixed story has five scenes.
    int len = 5;

    printf("A Dramatic Story: ");

    for (int i = 0; i < len; i++) {
        char scene = story[???]; // Select the current scene.
        
        if (scene == 'h') printf(":-)  ");
        if (scene == 's') printf(":-(  ");
        if (scene == 'n') printf(":-|  ");
    }

    printf("The End.\n");
    return 0;
}

// CHECK: A Dramatic Story: :-)  :-)  :-(  :-|  :-)  The End.

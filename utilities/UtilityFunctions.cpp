#include "UtilityFunctions.h"

void clearScreen() {
    printf("\033c");
}

bool kbhit() {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

char playerInput() {
    if(kbhit()) {
        return getch();    
    } else {
        return 0;
    }
}

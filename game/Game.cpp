#include "Game.h"

Game::Game() {
    int x = 20;
    int y = 0;
    DrawableEntity * entity = new DrawableEntity(x,y,"Hello");
    
    initscr();
    while(true) {
        entity->draw();
    }
    getch();
    endwin();
}

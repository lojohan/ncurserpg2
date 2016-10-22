#include "Game.h"

Game::Game() {
    int x = 10;
    int y = 0;
    Tile * tile = new Tile(x,y,"#");
    
    initscr();
    while(true) {
        tile->draw();
    }
    getch();
    endwin();
}

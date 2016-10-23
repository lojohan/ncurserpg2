#include "Game.h"

Game::Game() {
    
    
    initscr();
    
    menu_win = newwin(30,30,10,10);
    keypad(menu_win,true);
    
    clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    curs_set(0);
    fillTileMap();
    
    MovableEntity mve = *(new MovableEntity(10,10,"p"));
    
    while(true) {
        drawTiles();
        int ch = playerInput(this->menu_win);
        mve.move(ch);
        mve.draw();
        refresh();
    }
    endwin();
}

void Game::fillTileMap() {
    (this->map).parseMap();    
    for(std::vector<Tile>::iterator it = (this->map).getTileMap().begin(); it != (this->map).getTileMap().end(); ++it) {
        (this->tileList).push_back( *(it) );
    }
}

void Game::drawTiles() {
    for(std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it) {
        it->draw();
    }
}

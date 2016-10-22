#include "Game.h"

Game::Game() {
    
    initscr();
    curs_set(0);
    fillTileMap();
    
    while(true) {
        drawTiles();
    }
    getch();
    endwin();
}

void Game::fillTileMap() {
    (this->map).parseMap();    
    for(std::vector<Tile>::iterator it = (this->map).getTileMap().begin(); it != (this->map).getTileMap().end(); ++it) {
        (this->tileList).push_back( *(new Tile(it->getX(), it->getY(), it->getImage() )) );
    }
}

void Game::drawTiles() {
    for(std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it) {
        it->draw();
    }
}

#include "Game.h"

Game::Game() {
    
    this->init();
    
    // placeholder
    Player * player = new Player(10,10);
    mvEntityList.push_back(player);
    
    while(true) {
    
        this->draw();
        // placeholder
        int ch = playerInput(this->menu_win);
        updateMovables(ch);
        
    }
    
    this->end();
}

void Game::fillTileMap() {
    (this->map).parseMap();    
    for(std::vector<Tile>::iterator it = (this->map).getTileMap().begin(); it != (this->map).getTileMap().end(); ++it) {
        (this->tileList).push_back( (*it) );
    }
}

void Game::updateMovables(int ch) {
    for(std::vector<MovableEntity*>::iterator it = mvEntityList.begin(); it != mvEntityList.end(); ++it) {
        (*it)->move(ch);
    }
}

void Game::drawTiles() {
    for(std::vector<Tile>::iterator it = tileList.begin(); it != tileList.end(); ++it) {
        it->draw();
    }
}

void Game::drawMovables() {   
    for(std::vector<MovableEntity*>::iterator it = mvEntityList.begin(); it != mvEntityList.end(); ++it) {
        (*it)->draw();
    }
}

void Game::init() {
    initscr();
    
    menu_win = newwin(30,30,10,10);
    keypad(menu_win,true);
    
    clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    curs_set(0);
    fillTileMap();
}

void Game::end() {
    endwin();
}

void Game::clearBeforeDraw() {
    for(int i = 0; i < MENU_HEIGHT; i++) {
        for(int j = 0; j < MENU_WIDTH; j++) {
            mvprintw(i,j," ");
        }
    }
}

// separate drawing into spearate class 
void Game::draw() {
    clearBeforeDraw();
    drawTiles();
    drawMovables();
    refresh();
}

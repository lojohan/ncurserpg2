#include "Game.h"

Game::Game() {
    
    map = *(new Map());
    this->init();
    
    // placeholder
    this->player = new Player(10,10);
    mvEntityList.push_back(player);
    
    while(true) {
        this->draw();
        // placeholder
        int ch = playerInput(this->menu_win);
        updateMovables(ch);
        
    }
    
    this->end();
}

// build map
void Game::fillTileMap() {
    (this->map).parseMap( &(this->tileList) );
}

// run logic for movables
void Game::updateMovables(int ch) {
    for(std::vector<MovableEntity*>::iterator it = mvEntityList.begin(); it != mvEntityList.end(); ++it) {
        (*it)->move(ch);
    }
}

// separate drawing into spearate class 
//---------------------------------------------------------------------------------------------------------------------------------
void Game::drawTiles() {
    for(std::vector<Tile*>::iterator it = tileList.begin(); it != tileList.end(); ++it) {
        (*it)->draw();
    }
}

void Game::drawMovables() {   
    for(std::vector<MovableEntity*>::iterator it = mvEntityList.begin(); it != mvEntityList.end(); ++it) {
        (*it)->draw();
    }
}

void Game::draw() {
    clearBeforeDraw();
    drawTiles();
    drawMovables();
    refresh();
}

void Game::clearBeforeDraw() {
    for(int i = 0; i < MENU_HEIGHT; i++) {
        for(int j = 0; j < MENU_WIDTH; j++) {
            mvprintw(i,j," ");
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

// init and end stuff
//---------------------------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------------------------

#include "Game.h"

Game::Game() {
    
    map = *(new Map());
    this->init();
    
    // placeholder
    this->player = new Player(10,10);
    entityList.push_back(player);
    
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
    (this->map).parseMap( &(this->entityList) );
}

// run logic for movables
void Game::updateMovables(int ch) {
    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        if(MovableEntity* v = dynamic_cast<MovableEntity*>( *it )) {
            v->move(ch);
        }
    }
}

// separate drawing into spearate class 
//---------------------------------------------------------------------------------------------------------------------------------

void Game::drawEntities() {
    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        if(DrawableEntity* v = dynamic_cast<DrawableEntity*>( *it )) {
            v->draw();
        }
    }
}

void Game::draw() {
    clearBeforeDraw();
    drawEntities();
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
    setlocale(LC_ALL, "");
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

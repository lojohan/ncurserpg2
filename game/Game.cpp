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
        int ch = playerInput(this->game_window);
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
    physicsLoop(ch, this->entityList);
}

// separate drawing into spearate class 
//---------------------------------------------------------------------------------------------------------------------------------

void Game::drawEntities() {
    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        int arr[2];
        relativeCameraPos( *it, player, arr, GAME_HEIGHT, GAME_WIDTH);
        (*it)->draw(game_window, arr[0], arr[1]);
    }
}

void Game::draw() {
    clearBeforeDraw(game_window);
    drawEntities();
    wrefresh(game_window);
}

void Game::clearBeforeDraw(WINDOW * win) {
    for(int i = 0; i < GAME_HEIGHT; i++) {
        for(int j = 0; j < GAME_WIDTH; j++) {
            mvwprintw(win, i,j," ");
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

// init and end stuff
//---------------------------------------------------------------------------------------------------------------------------------
void Game::init() {
    setlocale(LC_ALL, "");
    initscr();
    
    super_window = newwin(GAME_HEIGHT+2,GAME_WIDTH+2,0,0);
    game_window = subwin(super_window, GAME_HEIGHT, GAME_WIDTH, 1, 1);
    box(super_window, 0, 0);
    touchwin(game_window);
    keypad(game_window,true);
    wrefresh(super_window);
    
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

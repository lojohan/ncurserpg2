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
    int color_count = 1;

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        int arr[2];
        relativeCameraPos( *it, player, arr, GAME_HEIGHT, GAME_WIDTH);
        init_pair(color_count, (*it)->getColor(), COLOR_BLACK);
        wattron(game_window, COLOR_PAIR(color_count));
        (*it)->draw(game_window, arr[0], arr[1]);
        wattroff(game_window, COLOR_PAIR(color_count));
        color_count++;
    }
}

void Game::drawGUI1Elements() {
    // placeholder
    mvwprintw(gui1_window,1,1,"Currently facing: %s", (player->getCurrentDirection()).c_str() );
}

void Game::drawGUI2Elements() {
    // placeholder
    mvwprintw(gui2_window,1,1,"Lorem Ipsum");
}

void Game::draw() {
    clearBeforeDraw(game_window, 0, 0, GAME_HEIGHT, GAME_WIDTH);
    clearBeforeDraw(gui1_window, 1, 1, GUI1_HEIGHT-2, GUI1_WIDTH-2);
    clearBeforeDraw(gui2_window, 1, 1, GUI2_HEIGHT-2, GUI2_WIDTH-2);
    
    drawEntities();
    
    drawGUI1Elements();
    drawGUI2Elements();
    
    wrefresh(super_window);
    
    refreshGUI1();
    refreshGUI2();
    refreshGameScreen();
    
}

void Game::clearBeforeDraw(WINDOW * win,int startX, int startY, int height, int width) {
    for(int i = startX; i < height; i++) {
        for(int j = startY; j < width; j++) {
            mvwprintw(win, i,j," ");
        }
    }
}

void Game::refreshGameScreen() {
    wrefresh(game_box);
    wrefresh(game_window);
}

void Game::refreshGUI1() {
    wrefresh(gui1_window);
}

void Game::refreshGUI2() {
    wrefresh(gui2_window);
}


//---------------------------------------------------------------------------------------------------------------------------------

// init and end stuff
//---------------------------------------------------------------------------------------------------------------------------------
void Game::init() {

    fillTileMap();
    initNCurses();
}

void Game::initNCurses() {
    setlocale(LC_ALL, "");
    initscr();
    
    start_color();
    
    createWindows();
    
    //init_pair(1,COLOR_RED, COLOR_BLACK);
    
    //wbkgd(game_window, COLOR_PAIR(1));
    
    keypad(game_window,true);
    wrefresh(super_window);
    
    refreshGUI1();
    refreshGUI2();
    refreshGameScreen();
    
    clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    curs_set(0);
}

void Game::createWindows() {
    super_window = newwin(GAME_HEIGHT+GUI2_HEIGHT+4,GAME_WIDTH+4+GUI1_WIDTH,0,0);
    
    game_box = subwin(super_window, GAME_HEIGHT+2,GAME_WIDTH+2,0,0);
    game_window = subwin(game_box, GAME_HEIGHT, GAME_WIDTH, 1, 1);
    
    gui1_window = subwin(super_window, GUI1_HEIGHT+2,GUI1_WIDTH+2,0,GAME_WIDTH+2);
    
    gui2_window = subwin(super_window, GUI2_HEIGHT+2,GUI2_WIDTH+2,GAME_HEIGHT+2,0);
    
    box(game_box,0,0);
    box(gui1_window,0,0);
    box(gui2_window,0,0);
    
    touchwin(gui1_window);
    touchwin(gui2_window);
    touchwin(game_window);
}

void Game::end() {
    endwin();
}
//---------------------------------------------------------------------------------------------------------------------------------

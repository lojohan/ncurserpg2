#include "Game.h"

Game::Game() {
}

void Game::start() {

    map = new Map();
    this->init();
    
    getPlayerFromEntities(&(this->player));
    
    while(true) {
        
        // placeholder
        int ch = playerInput(this->game_window);
        
        gameLoopInputHandler(ch, &game_paused);
        
        // run game logic here if not paused
        if(!game_paused) {
            updateMovables(ch, time_passed);
        }
        
        this->draw();
        
    }
    
    this->end();
}


// build map, will also build entities.
void Game::fillTileMap() {
    this->map->parseMap( &(this->entityList) );
}

// run logic for movables
void Game::updateMovables(int ch, int t) {
    physicsLoop(ch, this->entityList, t);
}

void Game::getPlayerFromEntities(Player ** player){
    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        if(Player* v = dynamic_cast<Player*>( *it )) {
            *player = v;
        }
    }
}

// separate drawing into spearate class 
//---------------------------------------------------------------------------------------------------------------------------------

void Game::drawEntities() {

    for(std::vector<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it) {
        // Array containing positions of entities relative to camera.
        int arr[2];
        relativeCameraPos( player, *it, arr, GAME_HEIGHT, GAME_WIDTH);
        
        // draws the entities in list of entities with the appropriate color.
        wattron(game_window, COLOR_PAIR( (*it)->getColor() ));
        //pos relative to player
        (*it)->draw(game_window, arr[0], arr[1]);
        
        //pos relative to 0,0
        //(*it)->draw(game_window, (*it)->getX(), (*it)->getY());
        
        wattroff(game_window, COLOR_PAIR( (*it)->getColor() ));
    }
}

void Game::drawPause() {
    std::string pauseString = "PAUSED";
    wattron(game_window, A_REVERSE);
    if(game_paused)
        mvwprintw(game_window,0,0,pauseString.c_str());
    wattroff(game_window, A_REVERSE);
    
}

// draw elements of GUI1
void Game::drawGUI1Elements() {
    // placeholder
    mvwprintw(gui1_window,1,1,"Currently facing: %s", (player->getCurrentDirection()).c_str() );
    mvwprintw(gui1_window,2,1,"Player position: X=%d, Y=%d", player->getX(), player->getY() );
    mvwprintw(gui1_window,3,1,"Game paused: %s", game_paused ? "true" : "false" );
    mvwaddwstr(gui1_window,4,1,L"HP: ♥♥♥♥♥♥");
}

// draw elements of GUI2
void Game::drawGUI2Elements() {
    // placeholder
    mvwprintw(gui2_window,1,1,"Lorem Ipsum");
}

// do all the drawing.
void Game::draw() {
    clearAll();
    
    drawEntities();
    
    drawPause();
    
    drawGUI1Elements();
    drawGUI2Elements();
    
    refreshAll();
    
}

// clears window by drawing white spaces.
void Game::clearBeforeDraw(WINDOW * win,int startX, int startY, int height, int width) {
    for(int i = startX; i < height; i++) {
        for(int j = startY; j < width; j++) {
            mvwprintw(win, i,j," ");
        }
    }
}

void Game::clearAll() {
    clearGameWindow();
    clearGUI1();
    clearBeforeDraw(gui2_window, 1, 1, GUI2_HEIGHT-2, GUI2_WIDTH-2);
}

void Game::clearGUI1() {
    clearBeforeDraw(gui1_window, 1, 1, GUI1_HEIGHT-2, GUI1_WIDTH-2);    
}

void Game::clearGameWindow() {
    clearBeforeDraw(game_window, 0, 0, GAME_HEIGHT, GAME_WIDTH);
}

// refresh game_window
void Game::refreshGameScreen() {
    wrefresh(game_box);
    wrefresh(game_window);
}

// refresh gui1
void Game::refreshGUI1() {
    wrefresh(gui1_window);
}

// refresh gui2
void Game::refreshGUI2() {
    wrefresh(gui2_window);
}

void Game::refreshAll() {
    refreshGUI1();
    refreshGUI2();
    refreshGameScreen();
    
    wrefresh(super_window);
}


//---------------------------------------------------------------------------------------------------------------------------------

// init and end stuff
//---------------------------------------------------------------------------------------------------------------------------------

// initializes ncurses, fills map with tiles.
// TODO: should also create entities on map.
void Game::init() {

    game_paused = false;
    fillTileMap();
    
    //this->player = new Player(10,10, true, L"\u03c3", COLOR_GREEN);
    
    //getPlayerFromEntities(this->player);
    initNCurses();
}

// inits things related to ncurses (graphics)
void Game::initNCurses() {
    setlocale(LC_ALL, "");
    initscr();
    
    start_color();
    initColors();
    
    createWindows();
    
    keypad(game_window,true);
    
    refreshAll();
    
    clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    curs_set(0);
}

// creates windows and boxes.
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

WINDOW * Game::getGameWindow() {
    return this->game_window;
}

WINDOW * Game::getGUI1Window() {
    return this->gui1_window;
}

// init color pairs

void Game::initColors() {
    for(int i = COLOR_RED; i <= COLOR_WHITE; i++) {
        init_pair(i, i, COLOR_BLACK);
    }
}

// closes all windows on close.
void Game::end() {
    endwin();
}
//---------------------------------------------------------------------------------------------------------------------------------

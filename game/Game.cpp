#include "Game.h"

Game::Game() {
}

void Game::start() {

    map = new Map();
    this->init();
    
    this->player = NULL; // initialize in case player is not found
    getPlayerFromEntities(&(this->player));
    
    addEntitiesToMap(this->entityMap, this->entityList);
    
    while(true) {
        
        // placeholder
        int ch = playerInput(this->game_window);
        
        gameLoopInputHandler(ch);
        
        // run game logic here if not paused
        if(!game_paused) {
            updateMovables(ch, time_passed);
        }
        
        this->draw();
        
        // Debugging key
        /*
        if (ch != -1) {
            mvwprintw(game_window, 0,0,"%d",ch);
            refreshAll();
        }
        */
        
    }
    
    this->end();
}


// build map, will also build entities.
void Game::fillTileMap() {
    this->map->parseMap( &(this->entityList), &(this->zoneList));
}

Map * Game::getMap() {
    return this->map;
}

std::vector<Entity*> Game::getEntities() {
    return this->entityList;
}

void Game::removeEntity(Entity * entity) {
	removeEntityFromMap(entityMap, entity);
	for (auto it = entityList.begin(); it != entityList.end(); it++) {
		if (*it == entity)
			entityList.erase(it);
	}
	delete entity;
}

void Game::removeEntityFromMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, Entity* entity) {
    std::stringstream s;
    s << entity->getX() << "," << entity->getY();
    std::string newCoords = s.str();

    if(entityMap.find(newCoords) != entityMap.end()) {
        std::vector<Entity*> * entities = &(entityMap.find(newCoords)->second);

        for (size_t i = 0; i < entities->size(); i++) {
            if (entities->at(i) == entity) {
                entities->erase(entities->begin() + i);
                if (entities->size() == 0) {
                    entityMap.erase(entityMap.find(newCoords));
                }
                break;
            }
        }
    }
}

void Game::addEntityToMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, Entity* entity) {
    std::stringstream s;
    s << entity->getX() << "," << entity->getY();
    std::string pos = s.str();

    if(entityMap.find(pos) != entityMap.end()) {
        std::vector<Entity*> * entitiesAtPoint = &(entityMap.find(pos)->second);
        entitiesAtPoint->push_back(entity);
    } else {
        std::vector<Entity*> entitiesAtPoint;
        entitiesAtPoint.push_back(entity);
        entityMap.insert({pos,entitiesAtPoint});
    }

}

void Game::addEntitiesToMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, std::vector<Entity*> entities) {
    int len = entities.size();
    
    for(int i = 0; i < len; i++) {
        addEntityToMap(entityMap,entities.at(i));
    }
}

void Game::clearEntityMap() {
    this->entityMap.clear();
}

// run logic for movables
void Game::updateMovables(int ch, int t) {
    physicsLoop(ch, this->entityList, this->entityMap,t);
}


Player * Game::getPlayer() {
	return player;
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
        drawEntity(game_window, *it, arr[0], arr[1]);

    }
}

void Game::drawEntity(WINDOW * window, Entity * e, int x, int y) {
    // draws the entities in list of entities with the appropriate color.
    wattron(window, COLOR_PAIR( e->getColor() ));
    e->draw(window, x, y);
    wattroff(window, COLOR_PAIR( e->getColor() ));    
}

void Game::drawPause() {
    std::string pauseString = "PAUSED";
    wattron(game_window, A_REVERSE);
    if(game_paused)
        mvwprintw(game_window,0,0,pauseString.c_str());
    wattroff(game_window, A_REVERSE);
    
}

std::string Game::getCurrentZoneNameforPlayer() {
    int l = zoneList.size();
    
    for(int i = 0; i < l; i++ ) {
        if(player->getX() >= zoneList.at(i)->x_upperleft  && player->getX() <= zoneList.at(i)->x_lowerright
            && player->getY() >= zoneList.at(i)->y_upperleft  && player->getY() <= zoneList.at(i)->y_lowerright) {
            return zoneList.at(i)->getName();
        } 
    }
    return "";
}

bool Game::getCurrentZoneFriendly() {
    int l = zoneList.size();
    
    for(int i = 0; i < l; i++ ) {
        if(player->getX() >= zoneList.at(i)->x_upperleft  && player->getX() <= zoneList.at(i)->x_lowerright
            && player->getY() >= zoneList.at(i)->y_upperleft  && player->getY() <= zoneList.at(i)->y_lowerright) {
            return zoneList.at(i)->friendly;
        } 
    }
    return false;
}

// draw elements of GUI1
void Game::drawGUI1Elements() {
    // placeholder
    mvwprintw(gui1_window,0,0,"Currently in: ");
    mvwprintw(gui1_window,1,0,"%s", getCurrentZoneNameforPlayer().c_str());
    mvwprintw(gui1_window,2,0,"Current Area is friendly: %s", getCurrentZoneFriendly() ? "true" : "false" );
    mvwprintw(gui1_window,3,0,"Currently facing: %s", (player->getCurrentDirection()).c_str() );
    mvwprintw(gui1_window,4,0,"Player position: X=%d, Y=%d", player->getX(), player->getY() );
    mvwprintw(gui1_window,5,0,"Game paused: %s", game_paused ? "true" : "false" );
    mvwaddwstr(gui1_window,6,0,L"HP: ♥♥♥♥♥♥");
    
}

// draw elements of GUI2
void Game::drawGUI2Elements() {
    // placeholder
    mvwprintw(gui2_window,0,0,"Lorem Ipsum");
}

// do all the drawing.
void Game::draw() {
    clearAll();
    
    drawTitle();
    
    drawEntities();
    
    drawPause();
    
    drawGUI1Elements();
    drawGUI2Elements();
    
    refreshAll();
    
}

void Game::drawTitle() {

    std::ifstream myfile ("res/Title.txt");
//    myfile.imbue(std::locale("en_US.UTF8"));
    myfile.seekg(0, std::ios::end);
    int len = myfile.tellg();
    myfile.seekg(0);
    char title[len+1];
    if (myfile.is_open())
    {
        myfile.read(title, len);
    }

mvwprintw(title_window,0,0,title);
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
    clearGUI2();
}

void Game::clearGUI1() {
    clearBeforeDraw(gui1_window, 0, 0, GUI1_HEIGHT, GUI1_WIDTH);    
}

void Game::clearGUI2() {
    clearBeforeDraw(gui2_window, 0, 0, GUI2_HEIGHT, GUI2_WIDTH);    
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
    wrefresh(gui2_box);
    wrefresh(gui1_window);
}

// refresh gui2
void Game::refreshGUI2() {
    wrefresh(gui2_box);
    wrefresh(gui2_window);
}

// refresh title
void Game::refreshTitle() {
    wrefresh(title_window);
}

void Game::refreshAll() {
    refreshGUI1();
    refreshGUI2();
    refreshGameScreen();
    refreshTitle();
    
    wrefresh(super_window);
}


//---------------------------------------------------------------------------------------------------------------------------------

// init and end stuff
//---------------------------------------------------------------------------------------------------------------------------------

// initializes ncurses, fills map with tiles.
// TODO: should also create entities on map.
void Game::init() {

	LOG.open("log.log", std::ofstream::out | std::ofstream::trunc);

    srand (time(NULL));

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
    std::cout << "Creating windows";
    super_window = newwin(GAME_HEIGHT+GUI2_HEIGHT+4+TITLE_HEIGHT+1,GAME_WIDTH+4+GUI1_WIDTH,0,0);
    
    title_window = subwin(super_window,TITLE_HEIGHT, TITLE_WIDTH,0,0);
    
    game_box = subwin(super_window, GAME_HEIGHT+2,GAME_WIDTH+2,TITLE_HEIGHT,0);
    game_window = subwin(game_box, GAME_HEIGHT, GAME_WIDTH, TITLE_HEIGHT+1, 1);
    
    gui1_box = subwin(super_window, GUI1_HEIGHT+2, GUI1_WIDTH+2, TITLE_HEIGHT, GAME_WIDTH+2);
    gui1_window = subwin(gui1_box, GUI1_HEIGHT,GUI1_WIDTH,TITLE_HEIGHT +1,GAME_WIDTH+3);
    
    gui2_box = subwin(super_window, GUI2_HEIGHT+2,GUI2_WIDTH+2,TITLE_HEIGHT+ GAME_HEIGHT+2,0);
    gui2_window = subwin(gui2_box, GUI2_HEIGHT,GUI2_WIDTH,TITLE_HEIGHT + GAME_HEIGHT+3,1);
    
    box(game_box,0,0);
    box(gui1_box,0,0);
    box(gui2_box,0,0);
    
    touchwin(title_window);
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

WINDOW * Game::getGUI2Window() {
    return this->gui2_window;
}

// init color pairs

void Game::initColors() {
    for(int i = COLOR_RED; i <= COLOR_WHITE; i++) {
        init_pair(i, i, COLOR_BLACK);
    }
}

void Game::togglePause() {
    this->game_paused = !(this->game_paused);
}

// closes all windows on close.
void Game::end() {
    endwin();
}
//---------------------------------------------------------------------------------------------------------------------------------

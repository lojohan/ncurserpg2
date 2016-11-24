#include "Game.h"

#include "../ui/UI.h"

#include "../ui/ncurses/NcursesUI.h"

Game::Game() {
	ui = new ncursesui::NcursesUI(*this);
}

void Game::start() {

    map = new Map();
    this->init();
    currentLevelID = "0";
    // placeholder
    this->entityList = entityLists.at(currentLevelID);
    this->zoneList = zoneLists.at(currentLevelID);
    
    this->player = NULL; // initialize in case player is not found
    getPlayerFromEntities(&(this->player));
    
    addEntitiesToMap(this->entityMap, this->entityList);
    
    while(true) {
        
        // placeholder
        int ch = ui->playerInput();
        
        gameLoopInputHandler(ch);
        
        // run game logic here if not paused
        if(!game_paused) {
            updateMovables(ch, time_passed);
        }
        
        ui->update(time_passed);
        
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

UI *Game::getUI() {
	return ui;
}

bool Game::isInBattle(){
	return false; // TODO !!
}

// build map, will also build entities.
void Game::fillTileMap() {
    this->map->parseMap( &(this->entityLists), &(this->zoneLists));
}

Map * Game::getMap() {
    return this->map;
}

std::vector<Entity*> &Game::getEntities() {
    return this->entityList;
}

void Game::removeEntity(Entity * entity) {
    detachEntity(entity);
	delete entity;
}

void Game::detachEntity(Entity * entity) {
	removeEntityFromMap(entityMap, entity);
	//LOG << "Removed entity from map " << std::endl;
	for (auto it = entityList.begin(); it != entityList.end(); it++) {
		if (*it == entity) {
			entityList.erase(it);
			break;
		}
	}
	//LOG << "Removed entity from entity list " << std::endl;
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
    //LOG << "Clearing entity map..." << std::endl;
    this->entityMap.clear();
}

// needs to handle adding player to the new level
void Game::switchLevel(std::string id, int newPlayerX, int newPlayerY) {
    LOG << "Entering level " << id <<  " at " << newPlayerX<<"," << newPlayerY  << std::endl;
    detachEntity(this->player);
    
    LOG << "Removed player from previous list " << std::endl;
    
    this->player->setX(newPlayerX);
    this->player->setY(newPlayerY);
    
    LOG << "Set new coords for player " << std::endl;
    
    entityLists.at(currentLevelID) = entityList;
    zoneLists.at(currentLevelID) = zoneList;
    currentLevelID = id;
    if (entityLists.find(id) == entityLists.end()) 
        LOG << "Map id " << id << " does not exist!" << std::endl;
    entityList = entityLists.at(id);
    zoneList = zoneLists.at(id);
    
    LOG << "Fetched new level " << std::endl;
    
    entityList.push_back(player);
    
    LOG << "Inserted player into new level " << std::endl;
    
    clearEntityMap();
    
    LOG << "Cleared entity map " << std::endl;
    
    addEntitiesToMap(this->entityMap, this->entityList);
    
    LOG << "Added new entities to entity map " << std::endl;

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





//---------------------------------------------------------------------------------------------------------------------------------

// init and end stuff
//---------------------------------------------------------------------------------------------------------------------------------

// initializes ncurses, fills map with tiles.
// TODO: should also create entities on map.
void Game::init() {

	init_logging();

    srand (time(NULL));

    game_paused = false;
    fillTileMap();
    
    ui->init();
}

bool Game::isPaused(){
	return this->game_paused;
}

void Game::togglePause() {
    this->game_paused = !(this->game_paused);
}

// closes all windows on close.
void Game::end() {
    endwin();
}
//---------------------------------------------------------------------------------------------------------------------------------

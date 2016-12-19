#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <unordered_map>
#include "../utilities/Point.h"
#include "../utilities/typedefs.h"
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../map/Map.h"
#include "../map/Zone.h"
#include "../physics/Physics.h"
#include "../ui/UI.h"

#define LIMITED_UPDATE 1
#define UPDATE_SIZE 20

class Map;

class Game {
    private: 
        std::unordered_map<std::string, std::vector<Entity*> > entityLists;
        std::vector<Entity*> entityList;
        std::unordered_map<std::string, std::vector<Zone*> > zoneLists;
        std::vector<Zone*> zoneList;
        std::unordered_map< std::string, std::vector<Entity*> > entityMap;
        
        Map * map;
        Player * player;
        
        bool game_paused;
        bool running;
        
        std::string currentLevelID;

        UI *ui;
		timespec diff(timespec start, timespec end);

    public:
        Game();
        
        void fillTileMap();
        Map * getMap();
        std::vector<Entity*> &getEntities();
        void removeEntity(Entity * entity);
        void detachEntity(Entity * entity);
        void removeEntityFromMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, Entity* entity);
        void addEntityToMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, Entity* entity);
        void addEntitiesToMap(std::unordered_map< std::string, std::vector<Entity*>> & entityMap, std::vector<Entity*> entities);
        void clearEntityMap();
        void switchLevel(std::string id, int newPlayerX, int newPlayerY);
        
        void init();
        
        void start();
        
        // closes all windows on close.
        void end();
        
        void togglePause();
        
        bool isPaused();

        std::string getCurrentZoneNameforPlayer();
        
        bool getCurrentZoneFriendly();
        
        // run logic for entities
        void updateMovables(Input input, long t);
        Player * getPlayer();
        void getPlayerFromEntities(Player ** player);
        
        bool isInBattle();

        void setUI(UI *ui);
        UI * getUI();
};

// The Game pointer!
extern Game * game;

#endif

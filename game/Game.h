#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../map/Map.h"
#include "../physics/Physics.h"

class Game {
    private: 
        //std::vector<Tile*> tileList;
        //std::vector<MovableEntity*> mvEntityList;
        std::vector<Entity*> entityList;
        Map map;
        Player * player;
        
        // should be in drawing bit
        WINDOW *super_window;
        WINDOW *game_window;
        const static int GAME_HEIGHT = 15;
        const static int GAME_WIDTH = 30;
        const static int START_X = 0;
        const static int START_Y = 0;

    public:
        Game();
        void fillTileMap();
        void init();
        void end();
        void updateMovables(int ch);
        
        // separate this drawing bit here
        void clearBeforeDraw(WINDOW * win);
        void drawEntities();
        void draw();
             
};

#endif

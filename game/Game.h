#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../map/Map.h"

class Game {
    private: 
        //std::vector<Tile*> tileList;
        //std::vector<MovableEntity*> mvEntityList;
        std::vector<Entity*> entityList;
        Map map;
        Player * player;
        
        // should be in drawing bit
        WINDOW *menu_win;
        const static int MENU_HEIGHT = 30;
        const static int MENU_WIDTH = 30;
        const static int START_X = 0;
        const static int START_Y = 0;

    public:
        Game();
        void fillTileMap();
        void init();
        void end();
        void updateMovables(int ch);
        
        // separate this drawing bit here
        void clearBeforeDraw();
        void drawEntities();
        void draw();
             
};

#endif

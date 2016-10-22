#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../map/Map.h"

class Game {
    private: 
        std::vector<Tile> tileList;
        Map map;

    public:
        Game();
        void fillTileMap();
        void drawTiles();
             
};

#endif

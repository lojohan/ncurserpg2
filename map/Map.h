#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"

class Map {
    protected:
        std::vector<Tile> tiles;
    
    public:
        Map();
        
        void parseMap();
        
        Tile getTileAtIndex(int i);
        
        std::vector<Tile> getMap();
};

#endif

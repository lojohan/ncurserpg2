#ifndef MAP_H
#define MAP_H

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
        
        void putTileInTileMap(Tile tile);
        
        Tile getTileAtIndex(int i);
        
        std::vector<Tile> getTileMap();
};

#endif

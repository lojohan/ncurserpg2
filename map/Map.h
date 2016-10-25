#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <fstream>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"

class Map {   
    public:
    
        Map();
        
        void parseMap(std::vector<Entity*> * tiles);
        
        void putTileInTileMap(Tile *tile,  std::vector<Entity*> * tiles);
        
        Tile* getTileAtIndex(int i);
};

#endif

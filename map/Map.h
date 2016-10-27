#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"

class Map {
    protected:
        std::string name;

    public:
    
        Map();
        
        void parseMap(std::vector<Entity*> * tiles);
        
        void putTileInTileMap(Tile *tile,  std::vector<Entity*> * tiles);
        
        Tile* getTileAtIndex(int i);
        
        void getImageFromImageMap(const wchar_t ** wch, int i );
};

#endif

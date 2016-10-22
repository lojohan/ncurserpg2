#ifndef TILE_H
#define TILE_H

#include "DrawableEntity.h"
#include <iostream>
#include <ncurses.h>
#include <string.h>

class Tile : public DrawableEntity {
    protected:
        bool walkable;
    
    public:
        Tile(int x, int y, std::string image);
        
        void setWalkable(bool walkable);
        
        bool getWalkable();
        
};

#endif

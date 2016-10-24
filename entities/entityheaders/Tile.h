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
        Tile(int x, int y, const wchar_t * image, bool walkable);
        
        void setWalkable(bool walkable);
        
        bool getWalkable();
        
};

#endif

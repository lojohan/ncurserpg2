#ifndef TILE_H
#define TILE_H

#include "Entity.h"
#include <iostream>
#include <ncurses.h>
#include <string.h>

class Tile : public Entity {
    protected:
        bool walkable;
    
    public:
        Tile(int x, int y, const wchar_t * image, bool walkable, bool solid, int color, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs);
        
        void setWalkable(bool walkable);
        
        bool getWalkable();
                
};

#endif

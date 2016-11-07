#ifndef TILE_H
#define TILE_H

#include "Entity.h"
#include <iostream>
#include <string.h>

class Tile : public Entity {
    protected:
        bool walkable;
    
    public:
        Tile(int x, int y, const wchar_t * image, std::string name, bool walkable, bool solid, int color, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs);
        
        void setWalkable(bool walkable);
        
        bool getWalkable();
                
};

#endif

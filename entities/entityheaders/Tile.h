#ifndef TILE_H
#define TILE_H

#include "Entity.h"
#include <iostream>
#include <string.h>

class Tile : public Entity {
    protected:
        bool walkable;
    
    public:
        Tile(int x, int y, std::string name, bool walkable, bool solid, Image image, Layer layer, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs);
        
        void setWalkable(bool walkable);
        
        bool getWalkable();
                
};

#endif

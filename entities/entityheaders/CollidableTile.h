#ifndef COLLIDABLETILE_H
#define COLLIDABLETILE_H

#include "Tile.h"
#include "CollidableEntity.h"
#include <iostream>
#include <string.h>

class CollidableTile : public Tile, public CollidableEntity {
    
    public:
        CollidableTile(int x, int y, const wchar_t * image, bool walkable, bool solid);
        void onCollision(CollidableEntity *ce);
        
};

#endif

#ifndef COLLIDABLEENTITY_H
#define COLLIDABLEENTITY_H

#include <iostream>
#include "Entity.h"
#include <string.h>

class CollidableEntity : public Entity {
    protected:
        bool solid;
        
    public:
        CollidableEntity(int x, int y, bool solid);
        
        void setSolid(bool solid);
        
        bool getSolid();
        
        void onCollision(CollidableEntity ce);
        
};

#endif

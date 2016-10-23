#ifndef COLLIDABLEENTITY_H
#define COLLIDABLEENTITY_H

#include <iostream>
#include <string.h>

class CollidableEntity {
    protected:
        bool solid;
        
    public:
        
        void setSolid(bool solid);
        
        bool getSolid();
        
        virtual void onCollision(CollidableEntity *ce) = 0;
        
};

#endif

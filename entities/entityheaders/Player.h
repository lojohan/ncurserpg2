#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "CollidableEntity.h"
#include "MovableEntity.h"
#include "DrawableEntity.h"
#include "Entity.h"
#include <string.h>

class Player : public MovableEntity, public CollidableEntity {
        
    public:
        Player(int x, int y);
        void move(int c);
        void moveUp();
        
        void moveDown();
        
        void moveLeft();
        
        void moveRight();
        
        void onCollision(CollidableEntity *ce);
        
};

#endif

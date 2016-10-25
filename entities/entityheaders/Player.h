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
        void getNextMove(int c, int arr[2]);
        
        void onCollision(CollidableEntity *ce);
        
};

#endif

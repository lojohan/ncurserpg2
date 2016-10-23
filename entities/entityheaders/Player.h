#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "CollidableEntity.h"
#include "MovableEntity.h"
#include <string.h>

class Player : public CollidableEntity, public MovableEntity {
        
    public:
        Player(int x, int y);
        void move(int c);
        
};

#endif

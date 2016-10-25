#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Entity.h"
#include <string.h>

class Player : public Entity {
    
    public:
        Player(int x, int y);
        void getNextMove(int c, int arr[2]);
        
        void onCollision(Entity *ce);
        
};

#endif

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Entity.h"
#include <string.h>

class Player : public Entity {
    
    public:
        Player(int x, int y, bool solid, const wchar_t * image, int color, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs);
        
};

#endif

#ifndef NPC_H
#define NPC_H

#include <iostream>
#include "Entity.h"
#include <string.h>

class NPC : public Entity {
    
    public:
        NPC(int x, int y, bool solid, const wchar_t * image, std::string name, int color,std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs);
        
};

#endif

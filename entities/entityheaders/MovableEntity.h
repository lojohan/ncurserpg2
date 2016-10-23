#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <iostream>
#include "DrawableEntity.h"

class MovableEntity : public DrawableEntity { 
    protected:
        void moveUp();
        
        void moveDown();
        
        void moveLeft();
        
        void moveRight();
     
    public:       
        MovableEntity(int x, int y, std::string image);
    
        void move(int c);
        
};

#endif

#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <iostream>
#include "DrawableEntity.h"

class MovableEntity : public DrawableEntity{ 
    protected:
        virtual void moveUp();
        
        virtual void moveDown();
        
        virtual void moveLeft();
        
        virtual void moveRight();
     
    public:       
    
        virtual void move(int c)=0;
        
};

#endif

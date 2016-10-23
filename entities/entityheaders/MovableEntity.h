#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <iostream>
#include "DrawableEntity.h"

class MovableEntity : public DrawableEntity{ 
    protected:
        virtual void moveUp()=0;
        
        virtual void moveDown()=0;
        
        virtual void moveLeft()=0;
        
        virtual void moveRight()=0;
     
    public:       
    
        virtual void move(int c)=0;
        
};

#endif

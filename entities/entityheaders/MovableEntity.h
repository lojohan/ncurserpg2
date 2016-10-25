#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include <iostream>
#include "DrawableEntity.h"

class MovableEntity : public DrawableEntity{ 
    protected:
     
    public:
    
        virtual void getNextMove(int c, int arr[2]) = 0;
    
        void move(int arr[2]);
        
};

#endif

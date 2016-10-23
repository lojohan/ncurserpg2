#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity {
    protected:
        int x, y;
        
    public:
        
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setCoords(int x, int y);
        
        virtual int getX();
        virtual int getY();
        
};

#endif

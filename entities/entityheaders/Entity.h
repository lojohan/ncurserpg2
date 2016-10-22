#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

class Entity {
    private:
        int x, y;
        
    public:
        Entity(int x, int y);
        
        void setX(int x);
        void setY(int y);
        void setCoords(int x, int y);
        
        int getX();
        int getY();
        
};

#endif

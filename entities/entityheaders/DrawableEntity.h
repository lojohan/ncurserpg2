#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include <iostream>
#include <ncurses.h>
#include "Entity.h"
#include <string.h>

class DrawableEntity : public Entity {
    protected:
        std::string image;
        
    public:
        DrawableEntity(int x, int y, std::string image);
        
        void setImage(std::string image);
        
        std::string getImage();
        
        void draw();
        
};

#endif

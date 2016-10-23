#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include "Entity.h"

class DrawableEntity : public Entity {
    protected:
        std::string image;
        
    public:
    
        void setImage(std::string image);
        
        std::string getImage();
        
        virtual void draw();
        
};

#endif

#ifndef DRAWABLEENTITY_H
#define DRAWABLEENTITY_H

#include <iostream>
#include <ncursesw/ncurses.h>
#include <string.h>
#include "Entity.h"

class DrawableEntity : public Entity {
    protected:
        const wchar_t * image;
        
    public:
    
        void setImage(const wchar_t * image);
        
        const wchar_t * getImage();
        
        virtual void draw();
        
};

#endif

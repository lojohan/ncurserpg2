#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <string.h>

class Entity {
    protected:
        int x, y;
        bool solid;
        const wchar_t * image;
        
    public:
        
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setCoords(int x, int y);
        
        virtual int getX();
        virtual int getY();
        
        // Movement
        virtual void getNextMove(int c, int arr[2]);
    
        void move(int arr[2]);
        
        // Collision
        void setSolid(bool solid);
        
        bool getSolid();
        
        virtual void onCollision(Entity *e);
        
        // Drawing
        void setImage(const wchar_t * image);
        
        const wchar_t * getImage();
        
        virtual void draw(WINDOW * win);
        virtual void draw(WINDOW * win, int x, int y);
        
};

#endif

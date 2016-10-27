#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <string.h>
#include <vector>

class Entity {

    protected:
    
        typedef void (*FnPtr)(Entity* entity1, Entity* entity2);
    
        std::vector<FnPtr> myCollisionFunctionPointers;
        
        enum Direction {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
        int x, y;
        bool solid;
        const wchar_t * image;
        Direction dir;
        int color;
        
    public:
        
        Entity(int x, int y, bool solid, const wchar_t * image, int color, std::vector<FnPtr> ptrs);
        
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setCoords(int x, int y);
        
        virtual int getX();
        virtual int getY();
        
        // Movement
        virtual void getNextMove(int c, int arr[2]);
        std::string getCurrentDirection();
    
        void move(int arr[2]);
        
        // Collision
        void setSolid(bool solid);
        
        bool getSolid();
        
        virtual void onCollision(Entity *e);
        
        // Drawing
        void setImage(const wchar_t * image);
        
        const wchar_t * getImage();
        virtual void setColor(int color);
        virtual int getColor();
        
        virtual void draw(WINDOW * win);
        virtual void draw(WINDOW * win, int x, int y);
        
};

#endif

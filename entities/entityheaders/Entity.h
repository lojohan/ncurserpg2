#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string.h>
#include <vector>
#include <time.h>
#include <ncursesw/ncurses.h>
#include "Character.h"
#include "../../game/Party.h"
#include "../../utilities/typedefs.h"

class Entity {

    protected:

    
        std::vector<ColFnPtr> myCollisionFunctionPointers;
        
        std::vector<MovFnPtr> movementPointers;
        
        std::vector<UseFnPtr> useKeyPointers;
        
        Party party;

        int x, y;
        bool solid;
        //const wchar_t * image;
        //int color;
        std::string name;
        Image image;
        
    public:
    
        enum Direction {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
        
        Direction dir;
        
        long t;
        
        Entity(int x, int y, bool solid, std::string name, Image image, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs);
        
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setCoords(int x, int y);
        
        virtual int getX();
        virtual int getY();
        
        virtual std::string getName();
        virtual void setName(std::string name);
        
        // Movement
        virtual void getNextMove(int c, int arr[2], long dt);
        const std::string getCurrentDirection();
        void setCurrentDirection(Direction dir);
    
        void move(int arr[2]);
        
        // Collision
        void setSolid(bool solid);
        
        bool getSolid();
        
        virtual void onCollision(Entity *e);
        
        virtual void onUse(Entity *e);
        
        // Drawing
        void setImage(Image image);
        
        Image getImage();
        virtual void setColor(int color);
        virtual int getColor();
        
        virtual void draw(WINDOW * win);
        virtual void draw(WINDOW * win, int x, int y);
        
        // Party!!!
        Party &getParty();
        bool isPartyDead();

};

#endif

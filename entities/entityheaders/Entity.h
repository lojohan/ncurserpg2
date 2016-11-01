#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <string.h>
#include <vector>
#include <time.h>
#include "Character.h"

class Entity {

    protected:
    
        typedef void (*ColFnPtr)(Entity* entity1, Entity* entity2);
        typedef void (*MovFnPtr)(Entity * e, int c, int arr[2], int dt);
    
        std::vector<ColFnPtr> myCollisionFunctionPointers;
        
        std::vector<MovFnPtr> movementPointers;
        
        std::vector<Character*> partyCharacters;
        
        int x, y;
        bool solid;
        const wchar_t * image;
        int color;
        
    public:
    
        enum Direction {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
        
        Direction dir;
        
        int t;
        
        Entity(int x, int y, bool solid, const wchar_t * image, int color, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs);
        
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setCoords(int x, int y);
        
        virtual int getX();
        virtual int getY();
        
        
        // Movement
        virtual void getNextMove(int c, int arr[2], int dt);
        std::string getCurrentDirection();
        void setCurrentDirection(Direction dir);
    
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
        
        // Party!!!
        void addPartyCharacter(Character * character);
        std::vector<Character * > getParty();
        bool isPartyDead();
        
};

#endif

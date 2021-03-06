#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string.h>
#include <vector>
#include <time.h>
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
        std::string name;
        Image image;
        
        int movingFrom[2];
        double movementProgress;

        double movementProgressPerMs;

    public:
    
        enum Direction {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
        
        enum Layer {FOREGROUND = 0, MIDDLE = 1, BACKGROUND = 2};
        
        Direction dir;
        
        Layer layer;
        
        long t;
        
        Entity(int x, int y, bool solid, std::string name, Image image, Layer layer, Direction dir, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs);
        
        virtual void setX(int x);
        virtual void setY(int y);
        virtual void setCoords(int x, int y);
        
        virtual int getX();
        virtual int getY();
        
        virtual double getMovementProgress();
        double getMovementX();
        double getMovementY();

        virtual std::string getName();
        virtual void setName(std::string name);
        

        virtual void update(long dt);

        // Movement
        virtual void getNextMove(Input input, int arr[2], long dt);
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
        
        Image &getImage();
        
        virtual void setColor(int color);
        virtual int getColor();
        
        /* 
        virtual void draw(WINDOW * win);
        virtual void draw(WINDOW * win, int x, int y);
        */
        
        // Party!!!
        Party &getParty();
        bool isPartyDead();

};

std::ostream& operator<<(std::ostream &strm, Entity &e);

#endif

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <wchar.h>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../utilities/FunctionPointerStuff.h"

class Map {

    protected:
        typedef void (*ColFnPtr)(Entity* entity1, Entity* entity2);
        typedef void (*MovFnPtr)(Entity * e, int c, int arr[2], int dt);
    
        std::string name;
        std::map<std::string,ColFnPtr> collisionFunctionMap;
        std::map<std::string,MovFnPtr> movementFunctionMap;

    public:
    
        Map();
        
        void parseMap(std::vector<Entity*> * tiles);
        
        void putEntityInMap(Entity * entity, std::vector<Entity*> * entities);
        
        Entity* getEntityAtIndex(int i);
        
        void getImageFromImageMap(const wchar_t ** wch, int i );
        
};

#endif

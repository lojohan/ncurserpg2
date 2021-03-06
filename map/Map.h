#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <wchar.h>
#include <boost/regex.hpp>
#include <boost/bind.hpp>
#include <sstream>
#include <cctype>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../utilities/FunctionPointerStuff.h"
#include "../utilities/typedefs.h"
#include "Zone.h"

#define CLASS_NAME 0
#define ENTITY_NAME 1
#define POSITION 2
#define SOLID 3
#define IMAGE 4
#define LAYER 5
#define DIRECTION 6
#define COLLISION 7
#define MOVEMENT 8
#define USE 9

#define ZONE_NAME 1
#define ZONE_POSITION1 2
#define ZONE_POSITION2 3
#define ZONE_FRIENDLY 4

class Map {
    protected:
    
        std::string name;
        std::map<std::string,ColFnPtr_unbound> collisionFunctionMap;
        std::map<std::string,MovFnPtr_unbound> movementFunctionMap;
        std::map<std::string,UseFnPtr_unbound> useFunctionMap;

        int * parseFunctionString(std::string * s, std::string * fname, int * count);

    public:
    
        Map();
        
        void parseMap(std::unordered_map<std::string,std::vector<Entity*> > * entityLists, std::unordered_map<std::string,std::vector<Zone*> > * zoneLists);
        
        void putEntityInMap(Entity * entity, std::vector<Entity*> * entities);
        
        void putZoneInList(Zone * zone, std::vector<Zone*> * zones);
        
        Entity* getEntityAtIndex(int i);
        
        void getImageFromImageMap(Image * image, int i );
        
};

#endif

#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <wchar.h>
#include <boost/regex.hpp>
#include <boost/bind.hpp>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../utilities/FunctionPointerStuff.h"
#include "../utilities/typedefs.h"

class Map {

    protected:
    
        std::string name;
        std::map<std::string,ColFnPtr_unbound> collisionFunctionMap;
        std::map<std::string,MovFnPtr_unbound> movementFunctionMap;
        std::map<std::string,UseFnPtr_unbound> useFunctionMap;
        
        bool parseFunctionString();

    public:
    
        Map();
        
        void parseMap(std::vector<Entity*> * tiles);
        
        void putEntityInMap(Entity * entity, std::vector<Entity*> * entities);
        
        Entity* getEntityAtIndex(int i);
        
        void getImageFromImageMap(const wchar_t ** wch, int i );
        
};

#endif

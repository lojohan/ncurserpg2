#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <sstream>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <time.h>
#include "../entities/Entities.h"
#include "../utilities/UtilityFunctions.h"
#include "../utilities/typedefs.h"


void physicsLoop(Input input, std::vector<Entity*> entityList,std::unordered_map< std::string,std::vector<Entity*> > & entityMap, long t);

#endif



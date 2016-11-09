#include "Map.h"

Map::Map(){
    collisionFunctionMap["doNothing"] = doNothing;
    
    //collision stuff
    collisionFunctionMap["teleportEntity"] = teleportEntity;
    collisionFunctionMap["changeColor"] = changeColor;
    //collisionFunctionMap["displayDialogue"] = displayDialogue;
    collisionFunctionMap["battle"] = battle;
    
    //movement stuff
    
    movementFunctionMap["noMove"] = noMove;
    movementFunctionMap["playerControl"] = playerControl;
    movementFunctionMap["randomAI"] = randomAI;
    
    //use stuff
    useFunctionMap["displayDialogue"] = displayDialogue;
    //useFunctionMap["changeColor"] = changeColor;
    
}

static boost::regex functionParseExpr("([^(]+)(?:\\((.*?)\\))?");

int * Map::parseFunctionString(std::string * s, std::string * fname, int * count) {
    boost::smatch matches;
    if (boost::regex_search(*s, matches, functionParseExpr)) {
        fname->assign(matches[1]);
        std::string paramsStr = matches[2];
        
        std::vector<std::string> paramsStrs;
        splitString( paramsStr, &paramsStrs, ' ');
        
        int * paramsInts = (int*) calloc(paramsStrs.size(), sizeof(int));
        
        for (size_t j = 0; j < paramsStrs.size(); j++) {
            paramsInts[j] = atoi( paramsStrs[j].c_str() );
        }
        
        *count = paramsStrs.size(); 
        //FILE * LOG_FILE = fopen("log.log", "a");
        //fprintf(LOG_FILE, "fname=%s, paramsStr=%s\n", fname.c_str(), paramsStr.c_str());
        //fclose(LOG_FILE);
      
        return paramsInts;
    }
    return NULL;
}

//TODO: clean and split into smaller functions.
void Map::parseMap(std::vector<Entity*> * tiles, std::vector<Zone*> * zones, std::unordered_map< std::string,std::vector<Entity*> > * entityMap) {
    
    // placeholder
    
    std::string line;
    std::ifstream myfile ("res/maps/randommap.txt");
    myfile.imbue(std::locale("en_US.UTF8"));
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {
            // skip comments
            if (line[0] == '#' || line.length() == 0)
                continue;

            boost::regex expr("\\s*");
            if(boost::regex_match(line,expr)) 
                continue;

            std::vector<std::string> splitstrings;
            
            splitString(line, &splitstrings, ';');
            
            const wchar_t * image;
            int pos[2];
            int color;
            std::vector<ColFnPtr> collisionpointers;
            std::vector<MovFnPtr> movementpointers;
            std::vector<UseFnPtr> usepointers;
            std::string name;
            
            std::string zone_name = "";
            int arr1[2];
            int arr2[2];
            bool friendlyArea = false;
            
            std::string className = splitstrings.at(CLASS_NAME);
            
            if(!className.compare("Player") || !className.compare("NPC") || !className.compare("Tile")) {
            
            // Gets various parameters from map file and constructs an object.
                for(size_t i = 1; i < splitstrings.size(); i++) {
                    
                    switch(i)
                    {	case ENTITY_NAME :
                        {
                            name = splitstrings.at(i);
                        break;
                        }
                    case POSITION :
                        {
                            std::vector<std::string> coords;
                            splitString( splitstrings.at(i), &coords, ',');
                            
                            
                            pos[0] = atoi( coords.at(0).c_str());
                            pos[1] = atoi( coords.at(1).c_str());
                            
                        break;
                        }
                    case IMAGE:
                        {
                            int value = atoi( splitstrings.at(i).c_str());
                            
                            getImageFromImageMap(&image,value);
                        break;
                        }
                    case COLOR:
                        {
                            color = atoi( splitstrings.at(i).c_str());
                        break;
                        }
                    case COLLISION:
                        {
                            std::vector<std::string> functionstrings;
                            splitString( splitstrings.at(i), &functionstrings, ',');
                            
                            for(std::vector<std::string>::iterator it = functionstrings.begin(); it != functionstrings.end(); ++it) {
                                std::string fname;
                                int count;
                                int * paramsInts;
                                if ( (paramsInts = parseFunctionString(&*it, &fname, &count)) != NULL) {                            
                                    ColFnPtr_unbound f = collisionFunctionMap[ fname ];
                                    ColFnPtr f_bound = boost::bind(f, _1, _2, count, paramsInts);
                                    collisionpointers.push_back(f_bound);
                                }
                            }
                        break;
                        }
                    case MOVEMENT:
                        {
                            std::vector<std::string> functionstrings;
                            splitString( splitstrings.at(i), &functionstrings, ',');
                            
                            for(std::vector<std::string>::iterator it = functionstrings.begin(); it != functionstrings.end(); ++it) {
                                std::string fname;
                                int count;
                                int * paramsInts;
                                if ( (paramsInts = parseFunctionString(&*it, &fname, &count)) != NULL) {                            
                                    MovFnPtr_unbound f = movementFunctionMap[ fname ];
                                    MovFnPtr f_bound = boost::bind(f, _1, _2, _3, _4, count, paramsInts);
                                    movementpointers.push_back(f_bound);
                                }
                            }
                        break;
                        }
                    case USE:
                        {
                            std::vector<std::string> functionstrings;
                            splitString( splitstrings.at(i), &functionstrings, ',');
                            
                            for(std::vector<std::string>::iterator it = functionstrings.begin(); it != functionstrings.end(); ++it) {
                                std::string fname;
                                int count;
                                int * paramsInts;
                                if ( (paramsInts = parseFunctionString(&*it, &fname, &count)) != NULL) {                            
                                    UseFnPtr_unbound f = useFunctionMap[ fname ];
                                    UseFnPtr f_bound = boost::bind(f, _1, _2, count, paramsInts);
                                    usepointers.push_back(f_bound);
                                }
                            }
                        break;
                        }
                    default:
                        break;
                    }

                }
                    
                if (!className.compare("Tile")) {
                    putEntityInMap( new Tile(pos[0],pos[1],image,name,true,true, color, collisionpointers, movementpointers, usepointers), tiles, entityMap);
                }
                if (!className.compare("Player")) {
                    putEntityInMap( new Player(pos[0],pos[1], true, image, name, color, collisionpointers, movementpointers, usepointers), tiles, entityMap);
                }
                if (!className.compare("NPC")) {
                    putEntityInMap( new NPC(pos[0],pos[1], true, image, name, color, collisionpointers, movementpointers, usepointers), tiles, entityMap);
                }
            } else if(!className.compare("Zone")) {
                
                for(size_t i = 1; i < splitstrings.size(); i++) {
                    
                    
                    switch(i) {
                        case ZONE_NAME :
                        {
                            zone_name = splitstrings.at(i);
                            break;
                        }
                        case ZONE_POSITION1 : 
                        {
                            std::vector<std::string> coords;
                            splitString( splitstrings.at(i), &coords, ',');
                            
                            
                            arr1[0] = atoi( coords.at(0).c_str());
                            arr1[1] = atoi( coords.at(1).c_str());
                            break;
                        }
                        case ZONE_POSITION2 :
                        {
                            std::vector<std::string> coords;
                            splitString( splitstrings.at(i), &coords, ',');
                            
                            
                            arr2[0] = atoi( coords.at(0).c_str());
                            arr2[1] = atoi( coords.at(1).c_str());
                            break;
                        }
                        case ZONE_FRIENDLY :
                        {
                            std::string friendly_string = splitstrings.at(i);
                            int friendly_int = atoi( friendly_string.c_str() );
                            
                            if(friendly_int != 0)
                                friendlyArea = true;
                            break;
                        }
                        default :
                        {
                            break;
                        }
                        
                    }
                    
                }
                
                putZoneInList( new Zone(zone_name, arr1, arr2, friendlyArea), zones);
                
            }
        }
    myfile.close();
    }

}

void Map::putEntityInMap(Entity * entity, std::vector<Entity*> * entities, std::unordered_map< std::string,std::vector<Entity*> > * entityMap) {
    entities->push_back(entity);
    std::stringstream s;
    s << entity->getX() << "," << entity->getY();
    std::string pos = s.str();
    
    //LOG("putEntityInMap",pos.c_str()); 
    
    if(entityMap->find(pos) != entityMap->end()) {
        //LOG("putEntityInMap2",pos.c_str()); 
        std::vector<Entity*> * entitiesAtPoint = &(entityMap->find(pos)->second);
        entitiesAtPoint->push_back(entity);
    } else {
        std::vector<Entity*> entitiesAtPoint;
        entitiesAtPoint.push_back(entity);
        entityMap->insert({pos,entitiesAtPoint}); 
    }
}

void Map::putZoneInList(Zone * zone, std::vector<Zone*> * zones) {
    zones->push_back(zone);
}

void Map::getImageFromImageMap(const wchar_t ** wch, int i ) {
    switch(i)
    {	case 1:
            *wch = L"#";
		break;
	case 2:
            *wch = L"\u00A2";
		break;
	case 3:
	        *wch = L"\u03C3";
	    break;
	default:
	        *wch = L"";
		break;
    }
}




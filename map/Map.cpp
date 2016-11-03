#include "Map.h"

Map::Map(){
    collisionFunctionMap["doNothing"] = doNothing;
    
    //collision stuff
    collisionFunctionMap["teleportEntity"] = teleportEntity;
    collisionFunctionMap["changeColor"] = changeColor;
    collisionFunctionMap["displayDialogue"] = displayDialogue;
    collisionFunctionMap["battle"] = battle;
    
    //movement stuff
    
    movementFunctionMap["noMove"] = noMove;
    movementFunctionMap["playerControl"] = playerControl;
    movementFunctionMap["randomAI"] = randomAI;
    
    //use stuff
    useFunctionMap["displayDialogue"] = displayDialogue;
    useFunctionMap["changeColor"] = changeColor;
}

//TODO: clean and split into smaller functions.
void Map::parseMap(std::vector<Entity*> * tiles) {
    
    // placeholder
    
    std::string line;
    std::ifstream myfile ("res/maps/map.txt");
    myfile.imbue(std::locale("en_US.UTF8"));
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {   
            std::vector<std::string> splitstrings;
            
            splitString(line, &splitstrings, ';');
            
            const wchar_t * image;
            int pos[2];
            int color;
            std::vector<ColFnPtr> collisionpointers;
            std::vector<MovFnPtr> movementpointers;
            std::vector<UseFnPtr> usepointers;
            std::string name;
            
            // Gets various parameters from map file and constructs an object.
            for(int i = 1; i < splitstrings.size(); i++) {
                
                switch(i)
                {	case 1 :
                    {
                        name = splitstrings.at(i);
                    break;
                    }
                case 2 :
                    {
                        std::vector<std::string> coords;
                        splitString( splitstrings.at(i), &coords, ',');
                        
                        
                        pos[0] = atoi( coords.at(0).c_str());
                        pos[1] = atoi( coords.at(1).c_str());
                        
                    break;
                    }
                case 3:
                    {
                        int value = atoi( splitstrings.at(i).c_str());
                        
                        getImageFromImageMap(&image,value);
                    break;
                    }
                case 4:
                    {
                        color = atoi( splitstrings.at(i).c_str());
                    break;
                    }
                case 5:
                    {
                        std::vector<std::string> functionstrings;
                        splitString( splitstrings.at(i), &functionstrings, ',');
                        
                        for(std::vector<std::string>::iterator it = functionstrings.begin(); it != functionstrings.end(); ++it) {
                            collisionpointers.push_back(collisionFunctionMap[ (*it) ]);
                        }
                    break;
                    }
                case 6:
                    {
                        std::vector<std::string> functionstrings;
                        splitString( splitstrings.at(i), &functionstrings, ',');
                        
                        for(std::vector<std::string>::iterator it = functionstrings.begin(); it != functionstrings.end(); ++it) {
                            movementpointers.push_back(movementFunctionMap[ (*it) ]);
                        }
                    break;
                    }
                case 7:
                    {
                        std::vector<std::string> functionstrings;
                        splitString( splitstrings.at(i), &functionstrings, ',');
                        
                        for(std::vector<std::string>::iterator it = functionstrings.begin(); it != functionstrings.end(); ++it) {
                            usepointers.push_back(useFunctionMap[ (*it) ]);
                        }
                    break;
                    }
                default:
                    break;
                }

            }
                
            if (!splitstrings.at(0).compare("Tile")) {
                putEntityInMap( new Tile(pos[0],pos[1],image,name,true,true, color, collisionpointers, movementpointers, usepointers), tiles);
            }
            if (!splitstrings.at(0).compare("Player")) {
                putEntityInMap( new Player(pos[0],pos[1], true, image, name, color, collisionpointers, movementpointers, usepointers), tiles);
            }
            if (!splitstrings.at(0).compare("NPC")) {
                putEntityInMap( new NPC(pos[0],pos[1], true, image, name, color, collisionpointers, movementpointers, usepointers), tiles);
            }
        }
    myfile.close();
    }

}

void Map::putEntityInMap(Entity * entity, std::vector<Entity*> * entities) {
    entities->push_back(entity);
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

#include "Map.h"

Map::Map(){

}

void Map::parseMap(std::vector<Entity*> * tiles) {
    
    // placeholder
    
    std::string line;
    std::ifstream myfile ("../res/maps/map.txt");
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {   
            std::vector<std::string> splitstrings;
            
            splitString(line, &splitstrings, ';');
            
            // TODO: rework to support additional types of things from map.
            
            const wchar_t * image;
            int pos[2];
            int color;
            
            // Gets various parameters from map file and constructs an object.
            for(int i = 1; i < splitstrings.size(); i++) {
                
                switch(i)
                {	case 1 :
                    {
                        std::vector<std::string> coords;
                        splitString( splitstrings.at(i), &coords, ',');
                        
                        
                        pos[0] = atoi( coords.at(0).c_str());
                        pos[1] = atoi( coords.at(1).c_str());
                        
                    break;
                    }
                case 2:
                    {
                        int value = atoi( splitstrings.at(i).c_str());
                        
                        getImageFromImageMap(&image,value);
                    break;
                    }
                case 3:
                    {
                        color = atoi( splitstrings.at(i).c_str());
                    }
                default:
                    break;
                }

            }
                
            if (!splitstrings.at(0).compare("Tile")) {
                
                putEntityInMap( new Tile(pos[0],pos[1],image,true,true, color, teleportEntity), tiles);
            }
            if (!splitstrings.at(0).compare("Player")) {
                putEntityInMap( new Player(pos[0],pos[1], true, image, color, teleportEntity), tiles);
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
		break;
    }
}

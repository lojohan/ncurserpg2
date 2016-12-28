#include "UtilityFunctions.h"

std::ofstream LOG;

void init_logging() {
    LOG.open("log.log", std::ofstream::out | std::ofstream::trunc);
}


//void clearScreen() {
//    printf(0,0,"\033c");
//}

void relativeCameraPos(int cx, int cy, int x, int y, int arr[2], int height, int width) {
    arr[0] = width/2 - cx + x;
    arr[1] = height/2 - cy + y;
}

void relativeCameraPosContinuous(double cx, double cy, double x, double y, double arr[2], double height, double width) {
    arr[0] = width/2 - cx + x;
    arr[1] = height/2 - cy + y;
}


void relativeCameraPos(Entity * centerentity, Entity * drawEntity, int arr[2], int height, int width) {
	relativeCameraPos(centerentity->getX(), centerentity->getY(), drawEntity->getX(), drawEntity->getY(), arr, height, width);
}

void gameLoopInputHandler(Input input) {
    switch(input)  {
        case PAUSE:
        {
            game->togglePause();
		    break;
	    }
        case DEBUG1:
		{
        	game->getUI()->displayDebug1();
			break;
		}
        case QUIT:
		{
			game->end();
			break;
		}
		default:
		    
		break;
    }
}

void splitString(std::string str_to_split, std::vector< std::string > * splits, char delimiter) {
    int prevsplit = 0;
    
    for(size_t i = 0; i < str_to_split.length(); i++) {
        char c = str_to_split[i];
        if(c == delimiter) {
            (*splits).push_back( str_to_split.substr(prevsplit,i-prevsplit) );
            prevsplit = i+1;
        } else if (i == str_to_split.length() -1 ) {
            (*splits).push_back( str_to_split.substr(prevsplit,i-prevsplit+1) );
        }
    }
}

// could use a map over all entities to determine neighbours
void useKeyBehaviour(Entity * e) {
    std::vector<Entity*> ents( game->getEntities() );
    int len = ents.size();
    
    for(int i = 0; i < len; i++) {
        switch(e->dir)
        {
            case Entity::NORTH:
                if(ents.at(i)->getY() == e->getY()-1 && ents.at(i)->getX() == e->getX()) {
                    ents.at(i)->onUse(e);
                }
            break;
            case Entity::SOUTH:
                if(ents.at(i)->getY() == e->getY()+1 && ents.at(i)->getX() == e->getX()) {
                    ents.at(i)->onUse(e);
                }
            break;
            case Entity::EAST:
                if(ents.at(i)->getY() == e->getY() && ents.at(i)->getX() == e->getX()+1) {
                    ents.at(i)->onUse(e);
                }
            break;
            case Entity::WEST:
                if(ents.at(i)->getY() == e->getY() && ents.at(i)->getX() == e->getX()-1) {
                    ents.at(i)->onUse(e);
                }
            break;
            default:
                break;
        }
    }
}

void getEntitiesForUpdate(std::vector<Entity*> &entities, int range, Entity * centerEntity, std::unordered_map< std::string, std::vector<Entity*> > &entityMap) {
    int posX = centerEntity->getX();
    int posY = centerEntity->getY();
    std::stringstream s;
    std::string coords;

    for(int i = posX - range; i < posX + range; i++) {
        for(int j = posY - range; j < posY + range; j++) {
            s << i << "," << j;
            coords = s.str();
            
            if(entityMap.find(coords) != entityMap.end()) {
                entities.insert( entities.end(), (entityMap.find(coords)->second).begin(), 
                                (entityMap.find(coords)->second).end());
            }
            s.str(std::string());
        }
    }
}




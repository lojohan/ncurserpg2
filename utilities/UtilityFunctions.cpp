#include "UtilityFunctions.h"

void clearScreen() {
    printf(0,0,"\033c");
}


int kbhit(int t1,int t2) {
  
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int playerInput(WINDOW *menu_win) {
    nodelay(stdscr, TRUE);
    if(kbhit(1,0)) {
        return wgetch(menu_win);    
    } else {
        return -1;
    }
}

int playerInputBlocking(WINDOW * menu_win) {
    return wgetch(menu_win);
}

void relativeCameraPos(Entity * centerentity, Entity * drawEntity, int arr[2], int height, int width) {
    arr[0] = height/2 - centerentity->getX() + drawEntity->getX();
    arr[1] = width/2 - centerentity->getY() + drawEntity->getY();
}

void gameLoopInputHandler(Entity * e, int c, int arr[2], int dt) {
    switch(c)
    {	case KEY_UP:
        {
            arr[0] = e->getX() - 1;
            e->dir = Entity::NORTH;
		break;
		}
	case KEY_DOWN:
	{
            arr[0] = e->getX() + 1;
            e->dir = Entity::SOUTH;
		break;
    }
	case KEY_LEFT:
	{
	        arr[1] = e->getY() - 1;
	        e->dir = Entity::WEST;
		break;
	}
	case KEY_RIGHT:
	{
	        arr[1] = e->getY() + 1;
	        e->dir = Entity::EAST;
		break;
	}
	case 'e':
	{
	    useKeyBehaviour(e);
	    break;
	}
    case 'p':
    {
        game->togglePause();
		break;
	}
	default:
		break;
    }
}

void splitString(std::string str_to_split, std::vector< std::string > * splits, char delimiter) {
    int prevsplit = 0;
    
    for(int i = 0; i < str_to_split.length(); i++) {
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
                if(ents.at(i)->getX() == e->getX()-1 && ents.at(i)->getY() == e->getY()) {
                    ents.at(i)->onUse(e);
                }
            break;
            case Entity::SOUTH:
                if(ents.at(i)->getX() == e->getX()+1 && ents.at(i)->getY() == e->getY()) {
                    ents.at(i)->onUse(e);
                }
            break;
            case Entity::EAST:
                if(ents.at(i)->getX() == e->getX() && ents.at(i)->getY() == e->getY()+1) {
                    ents.at(i)->onUse(e);
                }
            break;
            case Entity::WEST:
                if(ents.at(i)->getX() == e->getX() && ents.at(i)->getY() == e->getY()-1) {
                    ents.at(i)->onUse(e);
                }
            break;
            default:
                break;
        }
    }
}



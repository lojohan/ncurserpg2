#include "UtilityFunctions.h"

std::ofstream LOG;

//void clearScreen() {
//    printf(0,0,"\033c");
//}


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

void gameLoopInputHandler(int c) {
    switch(c)  {
        case 'p':
        {
            game->togglePause();
		    break;
	    }
        case KEY_F(1):
		{
        	game->clearAll();

        	mvwaddwstr(game->getGameWindow(), 0,0,L"");
        	for (int i = 1; i < 1000; i++) {
				const wchar_t * str;
				game->getMap()->getImageFromImageMap(&str, i);
				if (*str == '\0')
					break;
				waddwstr(game->getGameWindow(),str);
        	}
        	game->refreshAll();
        	playerInputBlocking(game->getGameWindow());
			break;
		}
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




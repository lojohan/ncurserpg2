#include "FunctionPointerStuff.h"

#include "../map/Map.h"
#include <sstream>
#include "../game/Battle.h"
#include "DialogueManager.h"

// functions to call on collision
void teleportEntity(Entity * e1, Entity * e2, int count, int * params) {
    if(count != 2) {
       e1->setY(9);
    } else {
       e1->setX(params[0]);
       e1->setY(params[1]);
    }
}

void doNothing(Entity * e1, Entity * e2, int count, int * params) {
}

void changeColor(Entity * e1, Entity * e2, int count, int * params) {
    int currentColor = e1->getColor();
    e1->setColor( (currentColor + 1) % 7 + 1 );
}

void displayDialogue(Entity * e1, Entity * e2, int count, int * params) {
    if (count != 1) {
        
    } else {
        if(Player* v = dynamic_cast<Player*>( e1 )) {
            game->clearGUI2();
            
            game->drawEntity(game->getGUI2Window(), e2, 0,0);
            
            std::string dialog = params[0] == 0 ? DialogueManager::getRandomDialogue() : DialogueManager::getDialogue(params[0]);
            
                            
            wattron(game->getGUI2Window(), COLOR_PAIR( e2->getColor() ));
            mvwprintw(game->getGUI2Window(), 0, 1, " %s: ", e2->getName().c_str());
            wattroff(game->getGUI2Window(), COLOR_PAIR( e2->getColor() ));
            
            wprintw(game->getGUI2Window(), "%s",  dialog.c_str());
            mvwprintw(game->getGUI2Window(), Game::GUI2_HEIGHT-1, 0, "▼");
            game->refreshAll();
            int c = 0;
            
            while( c != KEY_ENTER && c != ' ') {
                c = playerInputBlocking(game->getGameWindow());
            }
        }
    }

}

void battle(Entity * e1, Entity * e2, int count, int * params) {
    if(Player* player = dynamic_cast<Player*>( e1 )) {
    	Battle battleInstance(e1, e2);
    	battleInstance.commence();
    }
}

void enterLevel(Entity * e1, Entity * e2, int count, int * params) {
    LOG << "collision -> enterLevel" << std::endl;
    if( count != 3) {
    
    } else {
        if(Player* v = dynamic_cast<Player*>( e1 )) {
            game->switchLevel(std::to_string((long long int) params[0]),params[1],params[2]);
        }
    }
}

// functions to call when used


// functions to call on move

void noMove(Entity * e, int c, int arr[2], int dt, int count, int * params) {
}

void playerControl(Entity * e, int c, int arr[2], int dt, int count, int * params) {
    switch(c)
    {
    case KEY_UP:
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
	// ctrl+left
	case 540:
	{
	        e->setCurrentDirection( Entity::WEST );
		break;
	}
	case 555:
	{
	        e->setCurrentDirection( Entity::EAST );
		break;
	}
	case 561:
	{
	        e->setCurrentDirection( Entity::NORTH );
		break;
	}
	case 520:
	{
	        e->setCurrentDirection( Entity::SOUTH );
		break;
	}
	case 'e':
	{
	    useKeyBehaviour(e);
	    break;
	}
	default:
		break;
    }
}

void randomAI(Entity * e, int c, int arr[2], int dt, int count, int * params) {

    e->t += dt;
    if(e->t > 75000) {
        int output = (rand() % (int)(4));
        
        switch(output)
        {	case 0:
                arr[0] = e->getX() - 1;
                e->dir = Entity::NORTH;
		    break;
	    case 1:
                arr[0] = e->getX() + 1;
                e->dir = Entity::SOUTH;
		    break;
	    case 2:
	            arr[1] = e->getY() - 1;
	            e->dir = Entity::WEST;
		    break;
	    case 3:
	            arr[1] = e->getY() + 1;
	            e->dir = Entity::EAST;
		    break;
	    default:
		    break;
        }
        e->t = 0;
    }
}

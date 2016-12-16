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
        	std::string dialogue = params[0] == 0 ? DialogueManager::getRandomDialogue() : DialogueManager::getDialogue(params[0]);
        	game->getUI()->displayDialogue(e1, e2, dialogue);
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

void noMove(Entity * e, Input input, int arr[2], long dt, int count, int * params) {
}

void playerControl(Entity * e, Input input, int arr[2], long dt, int count, int * params) {
    switch(input)
    {
    case GO_UP:
        {
            arr[1] = e->getY() - 1;
            e->dir = Entity::NORTH;
		break;
		}
	case GO_DOWN:
	{
            arr[1] = e->getY() + 1;
            e->dir = Entity::SOUTH;
		break;
    }
	case GO_LEFT:
	{
	        arr[0] = e->getX() - 1;
	        e->dir = Entity::WEST;
		break;
	}
	case GO_RIGHT:
	{
	        arr[0] = e->getX() + 1;
	        e->dir = Entity::EAST;
		break;
	}
	case TURN_LEFT:
	{
	        e->setCurrentDirection( Entity::WEST );
		break;
	}
	case TURN_RIGHT:
	{
	        e->setCurrentDirection( Entity::EAST );
		break;
	}
	case TURN_UP:
	{
	        e->setCurrentDirection( Entity::NORTH );
		break;
	}
	case TURN_DOWN:
	{
	        e->setCurrentDirection( Entity::SOUTH );
		break;
	}
	case USE_KEY:
	{
	    useKeyBehaviour(e);
	    break;
	}
	default:
		break;
    }
}

void randomAI(Entity * e, Input input, int arr[2], long dt, int count, int * params) {
    
    if(count != 1) {
    } else {
        e->t += dt;
        if(e->t > params[0]) {
            int output = (rand() % (int)(4));
            
            switch(output)
            {	case 0:
                    arr[1] = e->getY() - 1;
                    e->dir = Entity::NORTH;
		        break;
	        case 1:
                    arr[1] = e->getY() + 1;
                    e->dir = Entity::SOUTH;
		        break;
	        case 2:
	                arr[0] = e->getX() - 1;
	                e->dir = Entity::WEST;
		        break;
	        case 3:
	                arr[0] = e->getX() + 1;
	                e->dir = Entity::EAST;
		        break;
	        default:
		        break;
            }
            e->t = 0;
        }
    }
}

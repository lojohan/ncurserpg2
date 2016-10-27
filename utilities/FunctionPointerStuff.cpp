#include "FunctionPointerStuff.h"

// functions to call on collision
void teleportEntity(Entity * e1, Entity * e2) {
    e1->setY(10);
}

void doNothing(Entity * e1, Entity * e2) {
}

void changeColor(Entity * e1, Entity * e2) {
    e1->setColor(7);
}

// functions to call on move

void noMove(Entity * e, int c, int arr[2], int dt) {
}

void playerControl(Entity * e, int c, int arr[2], int dt) {
    switch(c)
    {	case KEY_UP:
            arr[0] = e->getX() - 1;
            e->dir = Entity::NORTH;
		break;
	case KEY_DOWN:
            arr[0] = e->getX() + 1;
            e->dir = Entity::SOUTH;
		break;
	case KEY_LEFT:
	        arr[1] = e->getY() - 1;
	        e->dir = Entity::WEST;
		break;
	case KEY_RIGHT:
	        arr[1] = e->getY() + 1;
	        e->dir = Entity::EAST;
		break;
	default:
		break;
    }
}

void randomAI(Entity * e, int c, int arr[2], int dt) {

    e->t += dt;
    if(e->t > 250000) {
        srand (time(NULL));

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

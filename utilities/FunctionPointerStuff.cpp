#include "FunctionPointerStuff.h"

// functions to call on collision
void teleportEntity(Entity * e1, Entity * e2) {
    e1->setY(9);
}

void doNothing(Entity * e1, Entity * e2) {
}

void changeColor(Entity * e1, Entity * e2) {
    e1->setColor(6);
}

void displayDialogue(Entity * e1, Entity * e2) {
    if(Player* v = dynamic_cast<Player*>( e1 )) {
        game->clearGUI1();
        mvwprintw(game->getGUI2Window(), 0, 0, "This is my Dialogue. Stay a while and listen.");
        game->refreshAll();
        playerInputBlocking(game->getGameWindow());
    }
    
}

void battle(Entity * e1, Entity * e2) {
    if(Player* v = dynamic_cast<Player*>( e1 )) {
        bool fight = true;
        // vector containing all characters in this battle
        std::vector<Character*> fighters;
        
        fighters.insert(fighters.end(), ( e1->getParty() ).begin(), ( e1->getParty() ).end());
        
        std::vector<std::string> battleLog;
        battleLog.push_back("This is a battle log.");
        WINDOW * log_window = game->getGUI1Window();
        
        while(fight) {
            
        
            // Clear all windows
            game->clearAll();
            
            // draw Main battle window
            
            // draw menu battle window
            
            // draw battle log window
            for (int i= 0; i < battleLog.size(); i++) {
                mvwprintw(log_window, i, 0, battleLog.at(i).c_str());
            }
            
            // loop all characters and find who acts next
            
            // blocking input for player
            
            // run NPC actions
            
            // refresh all windows
            game->refreshAll();
            
            // check if battle is done
        }
    }
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

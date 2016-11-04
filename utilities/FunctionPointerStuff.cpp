#include "FunctionPointerStuff.h"

#include "../map/Map.h"
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
            
            mvwprintw(game->getGUI2Window(), 0, 1, " %s: %s", e2->getName().c_str(), dialog.c_str());
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
    if(Player* v = dynamic_cast<Player*>( e1 )) {
        bool fight = true;
        // vector containing all characters in this battle
        std::vector<Character*> fighters;
        
        fighters.insert(fighters.end(), ( e1->getParty() ).begin(), ( e1->getParty() ).end());
        fighters.insert(fighters.end(), ( e2->getParty() ).begin(), ( e2->getParty() ).end());
        
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
            if(e1->isPartyDead()) {
                // finish the fight
                fight = false;
            } else if( e2->isPartyDead()) {
                // finish the fight
                fight = false;
            }
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
    if(e->t > 250000) {
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

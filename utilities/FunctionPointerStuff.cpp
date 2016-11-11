#include "FunctionPointerStuff.h"

#include "../map/Map.h"
#include <sstream>
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

static std::vector<std::string> battleLog;

void drawBattleLog(WINDOW * log_window) {
	wclear(log_window);
	for (size_t i= 0; i < battleLog.size(); i++) {
		mvwprintw(log_window, i, 0, battleLog.at(i).c_str());
	}
}

void battle(Entity * e1, Entity * e2, int count, int * params) {
    if(Player* player = dynamic_cast<Player*>( e1 )) {
    	LOG << "Start battle between " << e1->getName() << " and " << e2->getName() << "\n";

        bool fight = true;
        
        WINDOW * log_window = game->getGUI1Window();
        WINDOW * menu_window = game->getGUI2Window();
        WINDOW * main_window = game->getGameWindow();
        
        mvwprintw(menu_window, 0, 0, "You are under attack by ");
        
        wattron(menu_window, COLOR_PAIR( e2->getColor() ));
        wprintw(menu_window, "%s", e2->getName().c_str());
        wattroff(menu_window, COLOR_PAIR( e2->getColor() ));
        wprintw(menu_window, "!");
        
        game->refreshAll();
        
        wgetch(menu_window);

        // vector containing all characters in this battle
        //std::vector<Character*> fighters;
        
        if (player->getParty().size() < 1) {
        	LOG << "error Players party is size " << player->getParty().size() << "!\n";
        	return;
        } else {
        	LOG << "Players party: " << player->getParty() << "\n";
        }
        if (e1->getParty().size() < 1) {
			LOG << "error Opponenets party is size " << e2->getParty().size() << "!\n";
			return;
		} else {
			LOG << "Opponents party: " << e2->getParty() << "\n";
		}

        //fighters.insert(fighters.end(), ( e1->getParty() ).begin(), ( e1->getParty() ).end());
        //fighters.insert(fighters.end(), ( e2->getParty() ).begin(), ( e2->getParty() ).end());
        
        battleLog.push_back("You have entered battle!");
        
        const char * items[] = { "Attack!", "Run!", "Meditate" };
        Menu battleMenu(menu_window, items, sizeof(items)/sizeof(char*), 0);

        int meditateCount = 0;

        while(fight) {

            // check if battle is done
            if(player->isPartyDead()) {
            	battleLog.push_back(player->getName() + "'s party died...");
                break;
            }
            if(e2->isPartyDead()) {
            	battleLog.push_back(e2->getName() + "'s party died...");
                break;
            }

            // Clear all windows
            game->clearAll();
            
            // draw battle log window
            drawBattleLog(log_window);

            // draw Main battle window
            {
				int my,mx;
				getmaxyx(main_window, my, mx);
				mvwprintw(main_window, 0, 0, e2->getName().c_str());
				for (int i = 0; i < e2->getParty().size(); i++) {
					mvwprintw(main_window, 2 + i, 0, e2->getParty()[i]->getName().c_str());
				}
				mvwprintw(main_window, my-1, 0, e1->getName().c_str());
				for (int i = 0; i < e1->getParty().size(); i++) {
					mvwprintw(main_window, my - 2 - e1->getParty().size() + i, 0, e1->getParty()[i]->getName().c_str());
				}
            }
            
            // draw battle menu window
            // not yet, do it when its players turn

            // loop all characters and find who acts next
            
            // blocking input for player
            while (!battleMenu.getInput()) {
            	// still selecting...
            }
            int selectedItem = battleMenu.getCurrentItemIndex();
            if (selectedItem == 0) {
            	//battleLog.push_back("You tried to Attack! But you missed..:(");

            	Character * target = e2->getParty()[0];

            	int dmgTaken = target->getMaxHp();
            	e2->getParty()[0]->setCurrentHp(0);

            	std::stringstream ss;
            	ss << e2->getName() << " took " << dmgTaken << " damage.";
            	battleLog.push_back(ss.str());
            }
            else if (selectedItem == 1) {
            	battleLog.push_back("You ran away!");
            	fight = false;
            	if (meditateCount == 3) {
            		for (int i = 0; i < player->getParty().size(); i++) {
            			player->getParty()[i]->setCurrentHp(0);
            		}
            	}
            }
            else if (selectedItem == 2) {
				battleLog.push_back(e1->getName() + " is meditating on the meaning of life.");
				meditateCount++;
			}
            else ;
            
            // run NPC actions

            drawBattleLog(log_window);
            // refresh all windows
            game->refreshAll();
        }

        wclear(log_window);
        wclear(menu_window);

        // draw battle log window
        drawBattleLog(log_window);
        //mvwprintw(menu_window, 0, 0, );

        game->refreshAll();

        wgetch(main_window);

        if (player->isPartyDead()) {
        	LOG << "Players party died! " << player->getParty() << "\n";
        	game->removeEntity(player);
		}
        if (e2->isPartyDead()) {
        	LOG << "Opponents party died! " << e2->getParty() << "\n";
        	game->removeEntity(e2);
        }
    }
    battleLog.clear();
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

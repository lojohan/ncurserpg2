/*
 * Battle.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: antolss
 */

#include "Battle.h"
#include "Game.h"

Battle::Battle(Entity * e1, Entity * e2) {
	this->e1 = e1;
	this->e2 = e2;
	log_window = game->getGUI1Window();
	menu_window = game->getGUI2Window();
	main_window = game->getGameWindow();
}

Battle::~Battle() {
}

bool Battle::checkPartySize(Entity * e1) {
	if (e1->getParty().size() < 1) {
		LOG << "error in battle for entity "<< e1->getName() << ", party size is " << e1->getParty().size() << "!\n";
		return true;
	} else {
		LOG << e1->getName() << "'s party: " << e1->getParty() << "\n";
		return false;
	}
}

void Battle::drawBattleLog() {
	wclear(log_window);
	for (size_t i= 0; i < battleLog.size(); i++) {
		mvwprintw(log_window, i, 0, battleLog.at(i).c_str());
	}
}

void Battle::commence() {

	LOG << "Start battle between " << e1->getName() << " and " << e2->getName() << "\n";

	bool fight = true;

	Player * player = game->getPlayer();

	mvwprintw(menu_window, 0, 0, "You are under attack by ");

	wattron(menu_window, COLOR_PAIR( e2->getColor() ));
	wprintw(menu_window, "%s", e2->getName().c_str());
	wattroff(menu_window, COLOR_PAIR( e2->getColor() ));
	wprintw(menu_window, "!");

	game->refreshAll();

	wgetch(menu_window);

	// vector containing all characters in this battle
	//std::vector<Character*> fighters;

	if (checkPartySize(e1) || checkPartySize(e2)) return;

	//fighters.insert(fighters.end(), ( e1->getParty() ).begin(), ( e1->getParty() ).end());
	//fighters.insert(fighters.end(), ( e2->getParty() ).begin(), ( e2->getParty() ).end());

	battleLog.push_back("You have entered battle!");

	const char * items[] = { "Attack!", "Run!", "Meditate" };
	Menu battleMenu(menu_window, items, sizeof(items)/sizeof(char*), 0);

	int meditateCount = 0;

	while(fight) {

		// check if battle is done
		if(e1->isPartyDead()) {
			battleLog.push_back(e1->getName() + "'s party died...");
			break;
		}
		if(e2->isPartyDead()) {
			battleLog.push_back(e2->getName() + "'s party died...");
			break;
		}

		// Clear all windows
		game->clearAll();

		// draw battle log window
		drawBattleLog();

		// draw Main battle window
		{
			int max_col,max_row;
			getmaxyx(main_window, max_row, max_col);
			mvwprintw(main_window, 0, 0, e2->getName().c_str());
			int row = 2;
			int col = 0;
			for (int i = 0; i < e2->getParty().size(); i++) {
				std::string name = e2->getParty()[i]->getName();
				if (col + (signed)name.length() > max_col) {
					if (col == 0) {
						name.resize(max_col);
					} else {
						row += 1;
						col = 0;
					}
				}
				mvwprintw(main_window, row, col, name.c_str());
				col += name.length() + 1;
			}
			mvwprintw(main_window, max_col-1, 0, e1->getName().c_str());
			for (int i = 0; i < e1->getParty().size(); i++) {
				mvwprintw(main_window, max_col - 2 - e1->getParty().size() + i, 0, e1->getParty()[i]->getName().c_str());
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

			for (size_t i = 0; i < e2->getParty().size(); i++) {
				Character * target = e2->getParty()[i];

				int dmgTaken = target->getMaxHp();
				target->setCurrentHp(0);

				std::stringstream ss;
				ss << target->getName() << " took " << dmgTaken << " damage.";
				battleLog.push_back(ss.str());
			}
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

		drawBattleLog();
		// refresh all windows
		game->refreshAll();
	}

	wclear(log_window);
	wclear(menu_window);

	// draw battle log window
	drawBattleLog();
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

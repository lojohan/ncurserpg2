/*
 * Battle.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: antolss
 */

#include "Battle.h"
#include "Game.h"

#include "../ui/UI.h"

Battle::Battle(Entity * e1, Entity * e2) {
	this->e1 = e1;
	this->e2 = e2;

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

void Battle::commence() {

	LOG << "Start battle between " << e1->getName() << " and " << e2->getName() << "\n";

	bool fight = true;

	Player * player = game->getPlayer();


	// vector containing all characters in this battle
	//std::vector<Character*> fighters;

	if (checkPartySize(e1) || checkPartySize(e2)) return;

	//fighters.insert(fighters.end(), ( e1->getParty() ).begin(), ( e1->getParty() ).end());
	//fighters.insert(fighters.end(), ( e2->getParty() ).begin(), ( e2->getParty() ).end());

	battleLog.push_back("You have entered battle!");

	const std::vector<std::string> items { "Attack!", "Run!", "Meditate" };

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



		// draw battle menu window
		// not yet, do it when its players turn

		// loop all characters and find who acts next

		// blocking input for player
		int selectedItem = game->getUI()->selectOption(items);
		//while (!battleMenu.getInput()) {
		//	// still selecting...
		//}
		//int selectedItem = battleMenu.getCurrentItemIndex();
		if (selectedItem == 0) {
			// user selected attack, select attacking character.

			Character * attacker = e1->getParty()[0];
			attacker->getAttackOptionsFns()[0];

			for (int i = 0; i < e2->getParty().size(); i++) {
				Character * target = e2->getParty()[i];

				int attackIndex = 0;

				const std::vector<Character*> attackers{attacker};
				const std::vector<Character*> targets{target};
				attacker->getAttackOptionsFns()[attackIndex](attackers, targets);

				std::stringstream ss;
				for (auto it = attackers.begin(); it != attackers.end(); it++) {
					ss << (*it)->getName();
					if (it != attackers.end() - 1) {
						ss << ", ";
					}
				}
				ss << " used " << attacker->getAttackOptionsNames()[attackIndex] << " on " << target->getName();
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

	}


	if (player->isPartyDead()) {
		LOG << "Players party died! " << player->getParty() << "\n";
		game->removeEntity(player);
	}
	if (e2->isPartyDead()) {
		LOG << "Opponents party died! " << e2->getParty() << "\n";
		game->removeEntity(e2);
	}
}

Entity *Battle::getEntity1(){
	return e1;
}

Entity *Battle::getEntity2() {
	return e2;
}


const std::vector<std::string>& Battle::getBattleLog() {
	return battleLog;
}


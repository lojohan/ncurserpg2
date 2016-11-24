/*
 * Battle.h
 *
 *  Created on: Nov 16, 2016
 *      Author: antolss
 */

#ifndef BATTLE_H_
#define BATTLE_H_

#include "../entities/Entities.h"

class Battle {
private:
	Entity * e1;
	Entity * e2;

	std::vector<std::string> battleLog;

	bool checkPartySize(Entity * e1);
	void drawBattleLog();

	void printTopParty(Entity * e);
	void printBottomParty(Entity * e);

public:
	Battle(Entity * e1, Entity * e2);
	virtual ~Battle();
	void commence();

	const std::vector<std::string>& getBattleLog();
	Entity *getEntity1();
	Entity *getEntity2();
};

#endif /* BATTLE_H_ */

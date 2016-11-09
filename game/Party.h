/*
 * Party.h
 *
 *  Created on: Nov 8, 2016
 *      Author: antolss
 */

#ifndef GAME_PARTY_H_
#define GAME_PARTY_H_

#include <ostream>
#include <vector>
#include "../entities/entityheaders/Character.h"

class Party {
	friend std::ostream& operator<<(std::ostream &strm, Party &p);
protected:
	std::vector<Character*> characters;
public:
	Party();
	void addCharacter(Character * character);
	void removeCharacter(Character * character);
	std::vector<Character*>& getCharacters();
	Character* getCharacter(int i);
	bool isAllDead();
	virtual ~Party();

	Character* operator[](int i);
	int size();
};

std::ostream& operator<<(std::ostream &strm, Party &p);


#endif /* GAME_PARTY_H_ */

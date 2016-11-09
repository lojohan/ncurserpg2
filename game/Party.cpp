/*
 * Party.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: antolss
 */

#include "Party.h"
#include "../utilities/UtilityFunctions.h"

Party::Party() {
}

Party::~Party() {
	LOG << "Disbanding party: " << *this << "\n";
	for (auto it = characters.begin(); it != characters.end(); it++) {
		delete *it;
	}
}

void Party::addCharacter(Character * character) {
	characters.push_back(character);
}

void Party::removeCharacter(Character * character) {
	for (auto it = characters.begin(); it != characters.end(); it++) {
		if (*it == character) {
			characters.erase(it);
			return;
		}
	}
}


bool Party::isAllDead() {
	for (auto it = characters.begin(); it != characters.end(); it++) {
		if ( ! (*it)->isDead() ) {
			return false;
		}
	}
	return true;
}

std::vector<Character*>& Party::getCharacters() {
	return this->characters;
}

Character* Party::getCharacter(int i) {
	return this->characters[i];
}

Character* Party::operator[](int i) {
	return getCharacter(i);
}

int Party::size() {
	return characters.size();
}

std::ostream& operator<<(std::ostream &strm, Party &p) {
  strm << "Party of size ";
  strm << p.size() << ":";
  for (auto it = p.characters.begin(); it != p.characters.end(); it++) {
	  strm << (it != p.characters.begin() ? ", " : " ") << **it;
  }
  strm << ".";
  return strm;
}

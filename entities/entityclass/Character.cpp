#include "../entityheaders/Character.h"

Character::Character(std::string name, int maxHp) :
		name(name), maxHp(maxHp), currentHp(maxHp) {
}

std::string Character::getName() {
	return this->name;
}

int Character::getMaxHp() {
	return this->maxHp;
}

int Character::getCurrentHp() {
	return this->currentHp;
}

void Character::setName(std::string name) {
	this->name = name;
}

void Character::setMaxHp(int maxHp) {
	this->maxHp = maxHp;
}

void Character::setCurrentHp(int currentHp) {
	this->currentHp = currentHp;
}

void Character::takeDamage(int dHp) {
	this->currentHp = std::max(0, currentHp - dHp);
}

bool Character::isDead() {
	return this->currentHp <= 0;
}

std::ostream& operator<<(std::ostream &strm, Character &c) {
  strm << "Character " << c.getName() <<" HP: "<< c.getCurrentHp() << '/' << c.getMaxHp();
  return strm;
}

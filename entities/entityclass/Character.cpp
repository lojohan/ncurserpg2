#include "../entityheaders/Character.h"
#include "../../utilities/UtilityFunctions.h"

#define assert_one_attacker(VEC) \
if ( (VEC) .size() != 1) { \
	LOG << __FUNCTION__ << " expected exacly 1 attacker, but got " << (VEC) .size(); \
}
#define assert_one_target(VEC) \
if (VEC.size() != 1) { \
	LOG << __FUNCTION__ << " expected exacly 1 target, but got " << VEC.size(); \
}

void unarmed_attack(std::vector<Character*> attackers, std::vector<Character*> targets) {

	//assert_one_attacker(attackers);
	//assert_one_target(targets);

	Character * attacker = attackers[0];
	Character * target = targets[0];

	int dmgTaken = target->getMaxHp();
	target->takeDamage(dmgTaken);

	//std::stringstream ss;
	//ss << target->getName() << " took " << dmgTaken << " damage.";
	//battleLog.push_back(ss.str());
}

Character::Character(std::string name, int maxHp) :
		name(name), maxHp(maxHp), currentHp(maxHp) {
	// TODO remove default attack options
	attackOptionsNames.push_back("Punch");
	attackOptionsFns.push_back(unarmed_attack);
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


const std::vector<std::string> Character::getAttackOptionsNames(){
	return attackOptionsNames;
}

const std::vector<AttackFnPtr> Character::getAttackOptionsFns(){
	return attackOptionsFns;
}

#include "../entityheaders/Character.h"

Character::Character(std::string name, int maxHp, int currentHp) {
    this->name = name;
    this->maxHp = maxHp;
    this->currentHp = currentHp;
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

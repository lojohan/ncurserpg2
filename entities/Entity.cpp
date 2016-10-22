#include "../entityheaders/Entity.h"

Entity::Entity(int x, int y) {
    this.x = x;
    this.y = y;
}

void Entity::setX(int x) {
    this.x = x;
}

void Entity::setY(int y){
    this.y = y;
}

void Entity::setCoords(int x, int y){
    this.x = x;
    this.y = y;
}

int Entity::getX(){
    return this.x;
}

int Entity::getY(){
    return this.y;
}

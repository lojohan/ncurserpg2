#include "../entityheaders/Entity.h"

void Entity::setX(int x) {
    this->x = x;
}

void Entity::setY(int y){
    this->y = y;
}

void Entity::setCoords(int x, int y){
    this->x = x;
    this->y = y;
}

int Entity::getX(){
    return this->x;
}

int Entity::getY(){
    return this->y;
}

void Entity::getNextMove(int c, int arr[2]) {
}

void Entity::move(int arr[2]) {
    this->setX(arr[0]);
    this->setY(arr[1]);
}

void Entity::setSolid(bool solid) {
    this->solid = solid;
}

bool Entity::getSolid() {
    return this->solid;
}

void Entity::onCollision(Entity *e) {
}

void Entity::setImage(const wchar_t * image) {
    this->image = image;
}
        
const wchar_t * Entity::getImage() {
    return this->image;
}

void Entity::draw(WINDOW *win) {
    mvwaddwstr(win, this->x, this->y, this->image);
}

void Entity::draw(WINDOW * win, int x, int y) {
    mvwaddwstr(win, x, y, this->image);
}

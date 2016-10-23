#include "../entityheaders/MovableEntity.h"

MovableEntity::MovableEntity(int x, int y, std::string image) : DrawableEntity(x,y,image) {
}

void MovableEntity::moveUp() {
    this->setX(this->getX()-1);
}
        
void MovableEntity::moveDown(){
    this->setX(this->getX()+1);
}
        
void MovableEntity::moveLeft(){
    this->setY(this->getY()-1);
}
        
void MovableEntity::moveRight(){
    this->setY(this->getY()+1);
}

void MovableEntity::move(int c) {
}

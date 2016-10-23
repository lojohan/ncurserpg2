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
    switch(c)
		{	case KEY_UP:
                    moveUp();
				break;
			case KEY_DOWN:
                    moveDown();
				break;
			case KEY_LEFT:
			        moveLeft();
				break;
			case KEY_RIGHT:
			        moveRight();
				break;
			default:
				break;
		}
}

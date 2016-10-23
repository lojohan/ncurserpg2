#include "../entityheaders/Player.h"

Player::Player(int x, int y) {
    this->image = "p";
    this->solid = true;
    this->x = x;
    this->y = y;
}

void Player::moveUp() {
    this->setX(this->getX()-1);
}
        
void Player::moveDown(){
    this->setX(this->getX()+1);
}
        
void Player::moveLeft(){
    this->setY(this->getY()-1);
}
        
void Player::moveRight(){
    this->setY(this->getY()+1);
}

void Player::move(int c) {
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

void Player::onCollision(CollidableEntity *ce) {
}

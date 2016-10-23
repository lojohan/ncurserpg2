#include "../entityheaders/Player.h"

Player::Player(int x, int y) : CollidableEntity(x,y,true), MovableEntity(x,y,"p") {
    this->image = "p";
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

#include "../entityheaders/Player.h"

Player::Player(int x, int y) {
    this->image = L"\u03c3";
    this->solid = true;
    this->x = x;
    this->y = y;
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

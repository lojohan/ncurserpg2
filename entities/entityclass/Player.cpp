#include "../entityheaders/Player.h"

Player::Player(int x, int y) {
    this->image = L"\u03c3";
    this->solid = true;
    this->setX(x);
    this->setY(y);
}

void Player::getNextMove(int c, int arr[2]) {
    switch(c)
    {	case KEY_UP:
            arr[0] = this->getX() - 1;
		break;
	case KEY_DOWN:
            arr[0] = this->getX() + 1;
		break;
	case KEY_LEFT:
	        arr[1] = this->getY() - 1;
		break;
	case KEY_RIGHT:
	        arr[1] = this->getY() + 1;
		break;
	default:
		break;
    }
}

void Player::onCollision(Entity *e) {
}

#include "../entityheaders/Player.h"

Player::Player(int x, int y) {
    this->image = L"\u03c3";
    this->solid = true;
    this->setX(x);
    this->setY(y);
    this->color = COLOR_GREEN;
}

void Player::getNextMove(int c, int arr[2]) {
    switch(c)
    {	case KEY_UP:
            arr[0] = this->getX() - 1;
            dir = NORTH;
		break;
	case KEY_DOWN:
            arr[0] = this->getX() + 1;
            dir = SOUTH;
		break;
	case KEY_LEFT:
	        arr[1] = this->getY() - 1;
	        dir = WEST;
		break;
	case KEY_RIGHT:
	        arr[1] = this->getY() + 1;
	        dir = EAST;
		break;
	default:
		break;
    }
}

void Player::onCollision(Entity *e) {
}

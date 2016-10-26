#include "../entityheaders/Entity.h"

Entity::Entity(int x, int y, bool solid, const wchar_t * image, int color) {
    this->image = image;
    this->solid = solid;
    this->setX(x);
    this->setY(y);
    this->color = color;
}

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

std::string Entity::getCurrentDirection() {
    switch(dir)
    {	case NORTH:
            return "NORTH";
		break;
	case SOUTH:
            return "SOUTH";
		break;
	case WEST:
	        return "WEST";
		break;
	case EAST:
            return "EAST";
		break;
	default:
		return "";
    }
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

int Entity::getColor() {
    return this->color;
}

void Entity::draw(WINDOW *win) {
    mvwaddwstr(win, this->x, this->y, this->image);
}

void Entity::draw(WINDOW * win, int x, int y) {
    mvwaddwstr(win, x, y, this->image);
}

#include "../entityheaders/Entity.h"

Entity::Entity(int x, int y, bool solid, const wchar_t * image, std::string name, int color, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs) {
    this->image = image;
    this->name = name;
    this->solid = solid;
    this->setX(x);
    this->setY(y);
    this->color = color;
    
    int l1 = collision_ptrs.size();
    for(int i = 0; i < l1; i++) {
        (this->myCollisionFunctionPointers).push_back( collision_ptrs.at(i));
    }
    
    int l2 = movement_ptrs.size();
    for(int i = 0; i < l2; i++) {
        (this->movementPointers).push_back( movement_ptrs.at(i));
    }
    
    int l3 = use_ptrs.size();
    for(int i = 0; i < l3; i++) {
        (this->useKeyPointers).push_back( use_ptrs.at(i));
    }
}


void Entity::setX(int x) {
    this->x = x;
}

void Entity::setY(int y){
    this->y = y;
}

std::string Entity::getName() {
    return this->name;
}

void Entity::setName(std::string name) {
    this->name = name;
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

void Entity::getNextMove(int c, int arr[2], int dt) {
    int l = movementPointers.size();
    
    for(int i = 0; i < l; i++) {
        (movementPointers.at(i))(this, c, arr, dt);
    }
}

const std::string Entity::getCurrentDirection() {
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

void Entity::setCurrentDirection(Direction dir) {
    this->dir = dir;
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
    int l = myCollisionFunctionPointers.size();
    
    for(int i = 0; i < l; i++) {
        (myCollisionFunctionPointers.at(i))(e,this);
    }
}

void Entity::onUse(Entity * e) {
    int l = useKeyPointers.size();
    
    for(int i = 0; i < l; i++) {
        (useKeyPointers.at(i))(e,this);
    }
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

void Entity::setColor(int color) {
    if(color > 0 && color < 8) {
        this->color = color;
    }
}

void Entity::draw(WINDOW *win) {
    mvwaddwstr(win, this->x, this->y, this->image);
}

void Entity::draw(WINDOW * win, int x, int y) {
    mvwaddwstr(win, x, y, this->image);
}

Party &Entity::getParty() {
    return party;
}

bool Entity::isPartyDead() {
    return party.isAllDead();
}





#include "../entityheaders/Entity.h"
#include "../../utilities/UtilityFunctions.h"

Entity::Entity(int x, int y, bool solid, std::string name, Image image, Layer layer, Direction dir, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs) {
    // placeholder
    this->dir = dir;

    this->movementProgress = 1;
    this->movementProgressPerMs = 0.004;

	this->image = image;
    this->name = name;
    this->solid = solid;
    this->setX(x);
    this->setY(y);
    this->layer = layer;
    
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

double Entity::getMovementProgress() {
	return movementProgress;
}

double Entity::getMovementX() {
	if (movementProgress >= 0 && movementProgress < 1){
		return this->movingFrom[0] + movementProgress * (this->x - this->movingFrom[0]);
	} else {
		return this->x;
	}
}
double Entity::getMovementY() {
	if (movementProgress >= 0 && movementProgress < 1){
		return this->movingFrom[1] + movementProgress * (this->y - this->movingFrom[1]);
	} else {
		return this->y;
	}
}

void Entity::update(long dt){};

void Entity::getNextMove(Input input, int arr[2], long dt) {
	if (movementProgress >= 0 && movementProgress < 1) {
		movementProgress += (dt/(double)1e6) /* in millis */ * movementProgressPerMs;
		if (!(movementProgress >= 0 && movementProgress < 1)) {
			movementProgress = 1;
		} else {
			return;
		}
	}

    int l = movementPointers.size();
    
    for(int i = 0; i < l; i++) {
    	if (movementPointers.at(i).empty()) {
    		LOG << "Movement pointer at index "<<i<<" for " << *this << " is empty!" << std::endl;
    	}
        (movementPointers.at(i))(this, input, arr, dt);
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
	this->movementProgress = 0;
	this->movingFrom={this->x, this->y};
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
    	if (myCollisionFunctionPointers.at(i).empty()) {
    		LOG << "CollisionFunctionPointer at index "<<i<<" for " << *this << " is empty!" << std::endl;
    	}
        (myCollisionFunctionPointers.at(i))(e,this);
    }
}

void Entity::onUse(Entity * e) {
    int l = useKeyPointers.size();
    
    for(int i = 0; i < l; i++) {
    	if (useKeyPointers.at(i).empty()) {
			LOG << "useKeyPointer at index "<<i<<" for " << *this << " is empty!" << std::endl;
		}
        (useKeyPointers.at(i))(e,this);
    }
}

void Entity::setImage(Image image) {
    this->image = image;
}
        
Image &Entity::getImage() {
    return this->image;
}

int Entity::getColor() {
    return this->image.color;
}

void Entity::setColor(int color) {
    if(color > 0 && color < 8) {
        this->image.color = color;
    }
}

Party &Entity::getParty() {
    return party;
}

bool Entity::isPartyDead() {
    return party.isAllDead();
}


std::ostream& operator<<(std::ostream &strm, Entity &e) {
  strm << "Entity< " << e.getName() <<" @ ("<< e.getX() << "," << e.getY() << ")" << " >";
  return strm;
}





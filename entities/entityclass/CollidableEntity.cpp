#include "../entityheaders/CollidableEntity.h"

CollidableEntity::CollidableEntity(int x, int y, bool solid) : Entity(x,y) {
    this->solid = solid;
}

void CollidableEntity::setSolid(bool solid) {
    this->solid = solid;
}

bool CollidableEntity::getSolid() {
    return this->solid;
}

void CollidableEntity::onCollision(CollidableEntity ce) {
}

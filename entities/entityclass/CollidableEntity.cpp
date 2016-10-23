#include "../entityheaders/CollidableEntity.h"

void CollidableEntity::setSolid(bool solid) {
    this->solid = solid;
}

bool CollidableEntity::getSolid() {
    return this->solid;
}

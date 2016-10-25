#include "../entityheaders/CollidableTile.h"

CollidableTile::CollidableTile(int x, int y, const wchar_t * image, bool walkable, bool solid) : Tile(x, y, image, walkable) {
    this->solid = solid;
}

void CollidableTile::onCollision(CollidableEntity *ce) {
}

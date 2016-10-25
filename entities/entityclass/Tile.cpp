#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, const wchar_t * image, bool walkable, bool solid) {
    this->x = x;
    this->y = y;
    this->walkable = walkable;
    this->image = image;
    this->solid = solid;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

void Tile::onCollision(Entity *e) {
}

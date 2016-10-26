#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, const wchar_t * image, bool walkable, bool solid, int color) : Entity(x, y, solid, image, color){
    this->walkable = walkable;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

void Tile::onCollision(Entity *e) {
}

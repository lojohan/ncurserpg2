#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, const wchar_t * image, bool walkable) {
    this->x = x;
    this->y = y;
    this->walkable = walkable;
    this->image = image;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

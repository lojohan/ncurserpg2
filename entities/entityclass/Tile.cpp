#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, std::string image, bool walkable) : DrawableEntity(x,y,image) {
    this->walkable = walkable;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

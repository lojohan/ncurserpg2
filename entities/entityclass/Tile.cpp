#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, std::string image) : DrawableEntity(x,y,image) {
    this->walkable = true;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, const wchar_t * image, bool walkable, bool solid, int color, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs) : Entity(x, y, solid, image, color, collision_ptrs, movement_ptrs){
    this->walkable = walkable;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

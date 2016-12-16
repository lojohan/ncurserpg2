#include "../entityheaders/Tile.h"

Tile::Tile(int x, int y, std::string name, bool walkable, bool solid, Image image, Layer layer, Direction dir, std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs) : Entity(x, y, solid, name, image, layer, dir, collision_ptrs, movement_ptrs, use_ptrs){
    this->walkable = walkable;
}

void Tile::setWalkable(bool walkable) {
    this->walkable = walkable;
}
        
bool Tile::getWalkable() {
    return this->walkable;
}

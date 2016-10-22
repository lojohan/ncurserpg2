#include "Map.h"

Map::Map() {
}

void Map::parseMap() {
    
}

Tile Map::getTileAtIndex(int i) {
    return (this->tiles).at(i);
}

std::vector<Tile> Map::getMap() {
    return this->tiles;
}

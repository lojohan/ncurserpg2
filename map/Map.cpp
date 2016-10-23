#include "Map.h"

Map::Map() {
}

void Map::parseMap() {
    for(int i = 0; i < 3; i++) {
        putTileInTileMap( *(new Tile(i,0,"#",false)) );
    }
}

void Map::putTileInTileMap(Tile tile) {
    (this->tiles).push_back(tile);
}

Tile Map::getTileAtIndex(int i) {
    return (this->tiles).at(i);
}

std::vector<Tile> Map::getTileMap() {
    return this->tiles;
}

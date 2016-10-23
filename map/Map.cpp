#include "Map.h"

Map::Map(){
}

void Map::parseMap(std::vector<Tile*> * tiles) {
    for(int i = 0; i < 3; i++) {
        putTileInTileMap( new Tile(i,0,"#",true), tiles);
    }
}

void Map::putTileInTileMap(Tile * tile, std::vector<Tile*> * tiles) {
    tiles->push_back(tile);
}

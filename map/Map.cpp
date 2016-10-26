#include "Map.h"

Map::Map(){
}

void Map::parseMap(std::vector<Entity*> * tiles) {
    for(int i = 0; i < 3; i++) {
        putTileInTileMap( new Tile(i+5,0,L"#",true,true, i+1), tiles);
    }
}

void Map::putTileInTileMap(Tile * tile, std::vector<Entity*> * tiles) {
    tiles->push_back(tile);
}

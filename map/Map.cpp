#include "Map.h"

Map::Map(){
}

void Map::parseMap(std::vector<Entity*> * tiles) {
    
    // placeholder
    
    int i = 0;
    std::string line;
    std::ifstream myfile ("../res/maps/map.txt");
    if (myfile.is_open())
    {
        while ( std::getline (myfile,line) )
        {   
            std::string substr1;
            std::string substr2;
            
            splitString(line, &substr1, &substr2, ',');
            
            if (!substr1.compare("Tile")) {
                putTileInTileMap( new Tile(5+i,0,L"#",true,true, i+1), tiles);
                i++;
            }
        }
    myfile.close();
    }

}

void Map::putTileInTileMap(Tile * tile, std::vector<Entity*> * tiles) {
    tiles->push_back(tile);
}

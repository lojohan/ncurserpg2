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
            std::vector<std::string> splitstrings;
            
            splitString(line, &splitstrings, ';');
            
            if (!splitstrings.at(0).compare("Tile")) {
                int value = atoi( splitstrings.at(1).c_str());
                
                const wchar_t * wch;
                
                getImageFromImageMap(&wch,value);
                
                putTileInTileMap( new Tile(5+i,0,wch,true,true, i+1), tiles);
                i++;
            }
        }
    myfile.close();
    }

}

void Map::putTileInTileMap(Tile * tile, std::vector<Entity*> * tiles) {
    tiles->push_back(tile);
}

void Map::getImageFromImageMap(const wchar_t ** wch, int i ) {
    switch(i)
    {	case 1:
            *wch = L"#";
		break;
	case 2:
            *wch = L"\u00A2";
		break;
	default:
		break;
    }
}

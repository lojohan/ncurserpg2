#include "Game.h"

Game::Game() {
    int x = 20;
    int y = 0;
    Entity * entity = new Entity(x,y);
    
    std::cout << "X: " << entity->getX() << ", Y: " << entity->getY();
}

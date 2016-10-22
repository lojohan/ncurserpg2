#include <iostream>
#include "entities/entityheaders/Entity.h"

using namespace std;

int main() {
    int x = 20;
    int y = 0;
    Entity * entity = new Entity(x,y);
    
    cout << "X: " << entity->getX() << ", Y: " << entity->getY();
}

#include "Zone.h"

Zone::Zone(std::string name, int upperleft[2], int lowerright[2]) {
    this->name = name;
    this->x_upperleft = upperleft[0];
    this->y_upperleft = upperleft[1];
    this->x_lowerright = lowerright[0];
    this->y_lowerright = lowerright[1];
}
        
std::string Zone::getName() {
    return this->name;
}

void Zone::setName(std::string name) {
    this->name = name;
}

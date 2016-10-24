#include "../entityheaders/DrawableEntity.h"

void DrawableEntity::setImage(std::string image) {
    this->image = image;
}
        
std::string DrawableEntity::getImage() {
    return this->image;
}

void DrawableEntity::draw() {
    const char * c = (this->image).c_str();
    mvprintw(this->x,this->y,c);
}

#include "../entityheaders/DrawableEntity.h"

DrawableEntity::DrawableEntity(int x, int y, std::string image) : Entity(x,y) {
    this->image = image;
}

void DrawableEntity::setImage(std::string image) {
    this->image = image;
}
        
std::string DrawableEntity::getImage() {
    return this->image;
}

void DrawableEntity::draw() {
    const char * c = (this->image).c_str();
    mvprintw(this->x,this->y,c);
    refresh();
}

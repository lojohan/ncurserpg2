#include "../entityheaders/DrawableEntity.h"

void DrawableEntity::setImage(const wchar_t * image) {
    this->image = image;
}
        
const wchar_t * DrawableEntity::getImage() {
    return this->image;
}

void DrawableEntity::draw() {
    //const char * c = (this->image).c_str();
    //mvprintw(this->x,this->y,c);
    //std::wstring widestr = std::wstring((this->image).begin(), (this->image).end());
    //const wchar_t * wcstr = widestr.c_str();
    
    mvaddwstr(this->x, this->y, this->image);
}

/*
 * Sprite.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#include <iostream>
#include "Sprite.h"


namespace sdlui {

Sprite::Sprite() :
		width(0), height(0), row(0), col(0), spritesheet(0)
{
}
Sprite::Sprite(int width, int height, int row, int col, SDL_Surface *spritesheet):
	width(width), height(height), row(row), col(col), spritesheet(spritesheet)
{
	if (width > spritesheet->w) {
		std::cerr << "width > spritesheet->w" << std::endl;
	}
	if (height > spritesheet->h) {
		std::cerr << "height > spritesheet->h" << std::endl;
	}
}

Sprite::~Sprite()
{

}

/*void Sprite::setSpriteIndex(int i) {
	if (spriteIndex % nOfSheetColumns >= nOfSheetRows) {
		std::cerr << "spriteIndex % nOfSheetColumns >= nOfSheetRow" << std::endl;
	}
	spriteIndex = i;
}
*/
void Sprite::drawOnSurface(SDL_Surface * screen, int x, int y) {
	SDL_Rect srcRect;
	srcRect.x = col * width;
	srcRect.y = row * height;
	srcRect.w = width;
	srcRect.h = height;
	SDL_Rect scrnPos;
	scrnPos.x = x;
	scrnPos.y = y;
	SDL_BlitSurface(spritesheet, &srcRect, screen, &scrnPos);
}










} /* namespace sdlui */

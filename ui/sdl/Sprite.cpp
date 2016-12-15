/*
 * Sprite.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#include <iostream>
#include "Sprite.h"


namespace sdlui {

Sprite::Sprite(int width, int height, int spriteIndex, SDL_Surface *spritesheet):
	spriteIndex(0), spritesheet(spritesheet),
	nOfSheetColumns(spritesheet->w / width),
	nOfSheetRows(spritesheet->h / height)
{
	setSpriteIndex(spriteIndex);
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

void Sprite::setSpriteIndex(int i) {
	if (spriteIndex % nOfSheetColumns >= nOfSheetRows) {
		std::cerr << "spriteIndex % nOfSheetColumns >= nOfSheetRow" << std::endl;
	}
	spriteIndex = i;
}

void Sprite::drawOnSurface(SDL_Surface * screen, int x, int y) {
	SDL_Rect srcRect;
	srcRect.x = (spriteIndex * SPRITE_W) % spritesheet->w;
	srcRect.y = (spriteIndex % nOfSheetColumns) * SPRITE_H;
	srcRect.w = SPRITE_W;
	srcRect.h = SPRITE_H;
	SDL_Rect scrnPos;
	scrnPos.x = x;
	scrnPos.y = y;
	SDL_BlitSurface(spritesheet, &srcRect, screen, &scrnPos);
}










} /* namespace sdlui */

/*
 * Sprite.h
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#ifndef UI_SDL_SPRITE_H_
#define UI_SDL_SPRITE_H_

#include <SDL/SDL.h>

#include "SdlUi.h"

namespace sdlui {

class Sprite {
private:
	int width, height, row, col;
	SDL_Surface *spritesheet;
	const int nOfSheetColumns, nOfSheetRows;

public:
	Sprite(int width, int height, int row, int col, SDL_Surface *spritesheet);
	virtual ~Sprite();

	//void setSpriteIndex(int i);
	void drawOnSurface(SDL_Surface * screen, int x, int y);
};

} /* namespace sdlui */

#endif /* UI_SDL_SPRITE_H_ */

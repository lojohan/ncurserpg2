/*
 * SdlUi.h
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#ifndef UI_SDL_SDLUI_H_
#define UI_SDL_SDLUI_H_

#include <SDL/SDL.h>

#include "../UI.h"

class BattleView;

namespace sdlui {

class SdlUi: public UI {
private:
	Game &game;
	BattleView * battleView;

	SDL_Surface *screen;
	SDL_Surface *sprite;


	void loadSprites();

public:
	SdlUi(Game &game);
	virtual ~SdlUi();

	void init();

	void deinit();

	void update(long dt);

	Input playerInput();

	void displayDialogue(Entity * e1, Entity * e2, std::string dialogue);

	int selectOption(const std::vector<std::string> &options);

	void startBattle(Battle &);

	void endBattle(Battle &);

	void displayDebug1();
};

} /* namespace sdlui */

#endif /* UI_SDL_SDLUI_H_ */

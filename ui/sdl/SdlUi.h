/*
 * SdlUi.h
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#ifndef UI_SDL_SDLUI_H_
#define UI_SDL_SDLUI_H_

#include <iomanip>
#include <SDL/SDL.h>
#include "../UI.h"

#define SPRITE_W 16
#define SPRITE_H 16
#define SCALE_FACTOR 3
#define RENDER_DISTANCE 10

class BattleView;

namespace sdlui {

class Sprite;
class EntityView;

extern EntityView *entityViews[10];

class SdlUi: public UI {
private:
	Game &game;
	BattleView * battleView;

	SDL_Surface *screen;

	void loadSprites();

	void drawEntities();

	SDL_Surface *loadSpritesheet(const char * path);

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
	
	void fpsinit();
	
	void fpsthink();
	
	void displayFPS();
};

} /* namespace sdlui */

#endif /* UI_SDL_SDLUI_H_ */

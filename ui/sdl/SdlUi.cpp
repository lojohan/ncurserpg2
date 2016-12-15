/*
 * SdlUi.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#include "SdlUi.h"
#include "Sprite.h"
#include "../../utilities/UtilityFunctions.h"
#include "../../entities/entityheaders/Entity.h"

namespace sdlui {

SdlUi::SdlUi(Game &game)
:game(game), battleView(NULL){
}

SdlUi::~SdlUi() {
	// TODO Auto-generated destructor stub
}

void SdlUi::init() {
	LOG << "Init sdl..." << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption("ADVAN", NULL);
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_ShowCursor( SDL_DISABLE ); // The cursor is ugly :(

    LOG << "Init sdl done." << std::endl;

    loadSprites();
}

void SdlUi::deinit() {
    SDL_Quit();
}

void SdlUi::loadSprites() {
	LOG << "Loading sprites..." << std::endl;
	SDL_Surface *temp   = SDL_LoadBMP("res/bmps/basictiles.bmp");
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));
	SDL_Surface *sheet = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	LOG << "Loading sprites done." << std::endl;

	static_sprites[0] = new Sprite(16, 16, 0, sheet);
	static_sprites[1] = new Sprite(16, 16, 1, sheet);
	static_sprites[2] = new Sprite(16, 16, 2, sheet);
	static_sprites[3] = new Sprite(16, 16, 3, sheet);
	static_sprites[4] = new Sprite(16, 16, 4, sheet);
	static_sprites[5] = new Sprite(16, 16, 5, sheet);
}

void SdlUi::update(long dt) {
	//LOG << "update in SDL UI..." << std::endl;
	drawEntities();
	SDL_Flip(screen);
}

void SdlUi::drawEntities() {

    for(auto it = game.getEntities().begin(); it != game.getEntities().end(); ++it) {
        // Array containing positions of entities relative to camera.
        int arr[2];
        //relativeCameraPos(game.getPlayer(), *it, arr, GAME_HEIGHT, GAME_WIDTH);
        //drawEntity(game_window, *it, arr[0], arr[1]);
        //LOG << "draw entity: " << **it << std::endl;
        int img = (*it)->getImage().id;
        int maxImg = sizeof(static_sprites)/sizeof(Sprite*);
        //LOG << "draw image id " << img << " / " << maxImg << std::endl;
        if (img >= maxImg) {
        	LOG << "Entity img is too high " << img << " >= " << maxImg << std::endl;
        	img = maxImg - 1;
        }
        int x = (*it)->getX() * SPRITE_W;
        int y = (*it)->getY() * SPRITE_H;

    	static_sprites[img]->drawOnSurface(screen, x, y);
    }
}

Input SdlUi::playerInput() {
	return Input::NONE;
}

void SdlUi::displayDialogue(Entity* e1, Entity* e2, std::string dialogue) {
}

int SdlUi::selectOption(const std::vector<std::string>& options) {
}

void SdlUi::startBattle(Battle& battle) {
}

void SdlUi::endBattle(Battle& battle) {
}

void SdlUi::displayDebug1() {
}

} /* namespace sdlui */

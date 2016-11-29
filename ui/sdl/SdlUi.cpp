/*
 * SdlUi.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: antolss
 */

#include "SdlUi.h"
#include "../../utilities/UtilityFunctions.h"

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
	SDL_Surface *temp   = SDL_LoadBMP("res/bmps/sprite.bmp");
	sprite = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	LOG << "Loading sprites done." << std::endl;
}

void SdlUi::update(long dt) {
	LOG << "update in SDL UI..." << std::endl;
	SDL_Rect scrnPos;
	scrnPos.x = 0;
	scrnPos.y = 0;
	scrnPos.w = 10;
	scrnPos.h = 10;
	SDL_BlitSurface(sprite, NULL, screen, &scrnPos);
	SDL_Flip(screen);
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

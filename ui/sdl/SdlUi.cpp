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


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

SDL_Surface* SDL_ScaleSurface(SDL_Surface *Surface)
{
	SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Surface->w * SCALE_FACTOR, Surface->h * SCALE_FACTOR, Surface->format->BitsPerPixel,
	        Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);
    for(Sint32 y = 0; y < Surface->h; y++) //Run across all Y pixels.
        for(Sint32 x = 0; x < Surface->w; x++) //Run across all X pixels.
            for(Sint32 o_y = 0; o_y < SCALE_FACTOR; ++o_y) //Draw _stretch_factor_y pixels for each Y pixel.
                for(Sint32 o_x = 0; o_x < SCALE_FACTOR; ++o_x) //Draw _stretch_factor_x pixels for each X pixel.
                    putpixel(_ret, static_cast<Sint32>(SCALE_FACTOR * x) + o_x,
                        static_cast<Sint32>(SCALE_FACTOR * y) + o_y, getpixel(Surface, x, y));

    return _ret;
}

void SdlUi::loadSprites() {
	LOG << "Loading sprites..." << std::endl;
	SDL_Surface *temp   = SDL_LoadBMP("res/bmps/basictiles.bmp");
	SDL_Surface *temp2 = SDL_ScaleSurface(temp);
	SDL_SetColorKey(temp2, SDL_SRCCOLORKEY, SDL_MapRGB(temp2->format, 255, 0, 255));
	SDL_Surface *sheet = SDL_DisplayFormat(temp2);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temp2);

	LOG << "Loading spritesheet done." << std::endl;

	int w = SPRITE_W*SCALE_FACTOR;
	int h = SPRITE_H*SCALE_FACTOR;

	static_sprites[0] = new Sprite(w, h,12, 0, sheet); // empty
	static_sprites[1] = new Sprite(w, h, 0, 0, sheet); //wall
	static_sprites[2] = new Sprite(w, h, 7, 3, sheet); // player
	static_sprites[3] = new Sprite(w, h, 6, 2, sheet);//house
	static_sprites[4] = new Sprite(w, h, 8, 0, sheet);//grass
	static_sprites[5] = new Sprite(w, h, 3, 6, sheet);//tree
	static_sprites[6] = new Sprite(w, h, 0, 4, sheet);// brown wall
	static_sprites[7] = new Sprite(w, h, 6, 7, sheet);// enemy npc
	static_sprites[8] = new Sprite(w, h, 7, 6, sheet);// friendly npc
	static_sprites[9] = new Sprite(w, h, 1, 5, sheet);// water

	LOG << "Loading sprites done." << std::endl;
}

void SdlUi::update(long dt) {
	//LOG << "update in SDL UI..." << std::endl;
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
	drawEntities();
	SDL_Flip(screen);
}

void SdlUi::drawEntities() {
	for (int layer = Entity::BACKGROUND; layer >= Entity::FOREGROUND; layer--) {
		for(auto it = game.getEntities().begin(); it != game.getEntities().end(); ++it) {
			if ((*it)->layer != layer) continue;
			int img = (*it)->getImage().id;
			int maxImg = sizeof(static_sprites)/sizeof(Sprite*);

			if (img >= maxImg) {
				LOG << "Entity img is too high " << img << " >= " << maxImg << std::endl;
				img = maxImg - 1;
			}

			// Center camera on player
			int pos[2]; // Array containing positions of entities relative to camera.
			relativeCameraPos(game.getPlayer(), *it, pos, screen->w / (SPRITE_W*SCALE_FACTOR), screen->h / (SPRITE_H*SCALE_FACTOR));

			static_sprites[img]->drawOnSurface(screen, pos[0]*(SPRITE_W*SCALE_FACTOR), pos[1]*(SCALE_FACTOR*SPRITE_H));
		}
	}
}

Input SdlUi::playerInput() {
	SDL_Event event;

	while (SDL_PollEvent (&event)) {
		/* We only care about SDL_KEYDOWN and SDL_KEYUP events */
		switch (event.type) {
		case SDL_KEYDOWN:

			switch(event.key.keysym.sym) {
			case SDLK_UP:
				return Input::GO_LEFT;
				break;
			case SDLK_DOWN:
				return Input::GO_RIGHT;
				break;
			case SDLK_LEFT:
				return Input::GO_UP;
				break;
			case SDLK_RIGHT:
				return Input::GO_DOWN;
				break;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			break;

		case SDL_QUIT:
			return Input::QUIT;
		default:
			break;
		}
	}
	return Input::NONE;
}

void SdlUi::displayDialogue(Entity* e1, Entity* e2, std::string dialogue) {
}

int SdlUi::selectOption(const std::vector<std::string>& options) {
	return 0; // TODO
}

void SdlUi::startBattle(Battle& battle) {
}

void SdlUi::endBattle(Battle& battle) {
}

void SdlUi::displayDebug1() {
}

} /* namespace sdlui */

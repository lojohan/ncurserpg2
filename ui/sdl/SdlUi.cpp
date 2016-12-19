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
#include "EntityView.h"

// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 10

namespace sdlui {

// An array to store frame times:
Uint32 frametimes[FRAME_VALUES];

// Last calculated SDL_GetTicks
Uint32 frametimelast;

// total frames rendered
Uint32 framecount;

// the value you want
float framespersecond;

EntityView *entityViews[10];

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
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) LOG << "Create SDL screen failed." << std::endl;
    //SDL_ShowCursor( SDL_DISABLE ); // The cursor is ugly :(

    //SDL_EnableKeyRepeat(200, 50);

    LOG << "Init sdl done." << std::endl;

    loadSprites();
    
    fpsinit();
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

SDL_Surface *SdlUi::loadSpritesheet(const char * path) {
	LOG << "Loading spritesheet:" << path << std::endl;
	SDL_Surface *temp   = SDL_LoadBMP(path);
	SDL_Surface *temp2 = SDL_ScaleSurface(temp);
	SDL_SetColorKey(temp2, SDL_SRCCOLORKEY, SDL_MapRGB(temp2->format, 255, 0, 255));
	SDL_Surface *sheet = SDL_DisplayFormat(temp2);
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temp2);
	LOG << "Loading spritesheet done:" << path << std::endl;
	return sheet;
}

/*
void SdlUi::loadSprite(int id) {

}*/
void SdlUi::loadSprites() {
	LOG << "Loading sprites..." << std::endl;

	SDL_Surface *tiles = loadSpritesheet("res/bmps/basictiles.bmp");
	SDL_Surface *chars = loadSpritesheet("res/bmps/characters.bmp");

	LOG << "Loading spritesheets done." << std::endl;

	entityViews[0] =  new StaticEntityView(12, 0, tiles); // empty
	entityViews[1] =  new DirectedEntityView(0, 0, 0, 1, 0, 2, 0, 3, tiles); //wall
	entityViews[2] =  new DirectedEntityView(3, 1, 2, 1, 0, 1, 1, 1, chars); // player
	entityViews[3] =  new StaticEntityView(6, 2, tiles);//house
	entityViews[4] =  new StaticEntityView(8, 0, tiles);//grass
	entityViews[5] =  new StaticEntityView(3, 6, tiles);//tree
	entityViews[6] =  new StaticEntityView(0, 4, tiles);// brown wall
	entityViews[7] =  new DirectedEntityView(3, 10, 2, 10, 0, 10, 1, 10, chars);// enemy npc
	entityViews[8] =  new DirectedEntityView(3, 7, 2, 7, 0, 7, 1, 7, chars);// friendly npc
	entityViews[9] =  new StaticEntityView(1, 5, tiles);// water

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
	    std::vector<Entity*> entities;
	    game.getEntitiesForUpdate(entities);
		for(auto it = entities.begin(); it != entities.end(); ++it) {
			if ((*it)->layer != layer) continue;

			// Center camera on player
			double pos[2]; // Array containing player offset relative to origo.
			relativeCameraPosContinuous(game.getPlayer()->getMovementX(), game.getPlayer()->getMovementY(), 0, 0, pos, screen->h / (SPRITE_H*SCALE_FACTOR), screen->w / (SPRITE_W*SCALE_FACTOR));

			entityViews[(*it)->getImage().id]->draw(screen, *it, pos[0], pos[1]);
		}
	}
	
	fpsthink();
	displayFPS();
	
}

void SdlUi::displayFPS() {
    std::stringstream fpsstream;
    fpsstream << std::fixed << std::setprecision(1) << framespersecond;

    std::stringstream caption;
    caption << "ADVAN      FPS: " << fpsstream.str();
    SDL_WM_SetCaption(caption.str().c_str(), NULL);
}

Input SdlUi::playerInput() {
	SDL_Event event;

	while (SDL_PollEvent (&event)) {
		/* We only care about SDL_KEYDOWN and SDL_KEYUP events */
		switch (event.type) {
		case SDL_KEYDOWN:

			/*switch(event.key.keysym.sym) {
			case SDLK_UP:
				return Input::GO_UP;
				break;
			case SDLK_DOWN:
				return Input::GO_DOWN;
				break;
			case SDLK_LEFT:
				return Input::GO_LEFT;
				break;
			case SDLK_RIGHT:
				//return Input::GO_RIGHT;
				break;
			default:
				break;
			}
			*/
			break;

		case SDL_KEYUP:
			break;

		case SDL_QUIT:
			return Input::QUIT;
		default:
			break;
		}
	}
	// Need to do this after SDL_PollEvent loop has run out!
	Uint8 *keystate = SDL_GetKeyState(NULL);
    if(keystate[SDLK_LCTRL]) {
       if (keystate[SDLK_UP]) {
		return Input::TURN_UP;
	    }
	    if (keystate[SDLK_RIGHT]) {
		    return Input::TURN_RIGHT;
	    }
	    if (keystate[SDLK_DOWN]) {
		    return Input::TURN_DOWN;
	    }
	    if (keystate[SDLK_LEFT]) {
		    return Input::TURN_LEFT;
	    } 
    }

	if (keystate[SDLK_UP]) {
		return Input::GO_UP;
	}
	if (keystate[SDLK_RIGHT]) {
		return Input::GO_RIGHT;
	}
	if (keystate[SDLK_DOWN]) {
		return Input::GO_DOWN;
	}
	if (keystate[SDLK_LEFT]) {
		return Input::GO_LEFT;
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

// This function gets called once on startup.
void SdlUi::fpsinit() {

        // Set all frame times to 0ms.
        memset(frametimes, 0, sizeof(frametimes));
        framecount = 0;
        framespersecond = 0;
        frametimelast = SDL_GetTicks();

}

void SdlUi::fpsthink() {

        Uint32 frametimesindex;
        Uint32 getticks;
        Uint32 count;
        Uint32 i;

        // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
        // This value rotates back to 0 after it hits FRAME_VALUES.
        frametimesindex = framecount % FRAME_VALUES;

        // store the current time
        getticks = SDL_GetTicks();

        // save the frame time value
        frametimes[frametimesindex] = getticks - frametimelast;

        // save the last frame time for the next fpsthink
        frametimelast = getticks;

        // increment the frame count
        framecount++;

        // Work out the current framerate

        // The code below could be moved into another function if you don't need the value every frame.

        // I've included a test to see if the whole array has been written to or not. This will stop
        // strange values on the first few (FRAME_VALUES) frames.
        if (framecount < FRAME_VALUES) {

                count = framecount;

        } else {

                count = FRAME_VALUES;

        }

        // add up all the values and divide to get the average frame time.
        framespersecond = 0;
        for (i = 0; i < count; i++) {

                framespersecond += frametimes[i];

        }

        framespersecond /= count;

        // now to make it an actual frames per second value...
        framespersecond = 1000.f / framespersecond;

}

} /* namespace sdlui */

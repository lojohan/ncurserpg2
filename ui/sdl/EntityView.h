/*
 * EntityView.h
 *
 *  Created on: Dec 15, 2016
 *      Author: antolss
 */

#ifndef UI_SDL_ENTITYVIEW_H_
#define UI_SDL_ENTITYVIEW_H_

#include "SdlUi.h"
#include "Sprite.h"

class Entity;

namespace sdlui {


class EntityView {
public:
	virtual ~EntityView();
	/* offsetx and y is tile x and y !!! */
	virtual void draw(SDL_Surface * screen, Entity *e, int offsetx, int offsety){};
};
class StaticEntityView : public EntityView{
	Sprite sprite;
public:
	StaticEntityView(int row, int col, SDL_Surface *sheet);

	/* offsetx and y is tile x and y !!! */
	void draw(SDL_Surface * screen, Entity *e,  int offsetx, int offsety);
};

class DirectedEntityView : public EntityView{
	Sprite sprite[4];
public:
	DirectedEntityView(int row1, int col1, int row2, int col2, int row3, int col3, int row4, int col4, SDL_Surface *sheet);

	// offsetx and y is tile x and y !!!
	void draw(SDL_Surface * screen, Entity *e,  int offsetx, int offsety);
};

} /* namespace sdlui */

#endif /* UI_SDL_ENTITYVIEW_H_ */

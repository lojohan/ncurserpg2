/*
 * EntityView.cpp
 *
 *  Created on: Dec 15, 2016
 *      Author: antolss
 */

#include "EntityView.h"

#include "../../entities/entityheaders/Entity.h"

namespace sdlui {


EntityView::~EntityView() {
	// TODO Auto-generated destructor stub
}

StaticEntityView::StaticEntityView(int row, int col, SDL_Surface *sheet):
	sprite(SPRITE_W*SCALE_FACTOR, SPRITE_H*SCALE_FACTOR , row, col, sheet)
{
}

/* offsetx and y is tile x and y !!! */
void StaticEntityView::draw(SDL_Surface * screen, Entity *e,  double offsetx, double offsety){
	sprite.drawOnSurface(screen, (e->getX()+offsetx)*(SPRITE_W*SCALE_FACTOR), (e->getY()+offsety)*(SCALE_FACTOR*SPRITE_H));
}

enum Direction {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};

DirectedEntityView::DirectedEntityView(int row1, int col1, int row2, int col2, int row3, int col3, int row4, int col4, SDL_Surface *sheet)
{
	sprite[NORTH] = Sprite( SPRITE_W * SCALE_FACTOR, SPRITE_H * SCALE_FACTOR, row1,
			col1, sheet);
	sprite[EAST] = Sprite(SPRITE_W * SCALE_FACTOR, SPRITE_H * SCALE_FACTOR, row2,
			col2, sheet);
	sprite[SOUTH] = Sprite(SPRITE_W * SCALE_FACTOR, SPRITE_H * SCALE_FACTOR, row3,
			col3, sheet);
	sprite[WEST] = Sprite(SPRITE_W * SCALE_FACTOR, SPRITE_H * SCALE_FACTOR, row4,
			col4, sheet);
}

// offsetx and y is tile x and y !!!
void DirectedEntityView::draw(SDL_Surface * screen, Entity *e, double offsetx, double offsety){
	sprite[e->dir].drawOnSurface(screen, (e->getMovementX()+offsetx)*(SPRITE_W*SCALE_FACTOR), (e->getMovementY()+offsety)*(SCALE_FACTOR*SPRITE_H));
}






} /* namespace sdlui */

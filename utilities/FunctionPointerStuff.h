#ifndef FUNCTIONPOINTERSTUFF_H
#define FUNCTIONPOINTERSTUFF_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <ncurses.h>
#include "../utilities/UtilityFunctions.h"
#include "../entities/Entities.h"
#include "../game/Game.h"

// functions which can be called on collision
void teleportEntity(Entity * e1, Entity * e2);

void doNothing(Entity * e1, Entity * e2);

void changeColor(Entity * e1, Entity * e2);

void displayDialogue(Entity * e1, Entity * e2);

void battle(Entity * e1, Entity * e2);

// functions to call on move
void noMove(Entity * e, int c, int arr[2], int dt);

void playerControl(Entity * e, int c, int arr[2], int dt);

void randomAI(Entity * e, int c, int arr[2], int dt);

#endif

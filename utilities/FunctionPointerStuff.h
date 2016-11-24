#ifndef FUNCTIONPOINTERSTUFF_H
#define FUNCTIONPOINTERSTUFF_H

#include <vector>
#include <string>
#include <stdlib.h>
#include "../entities/Entities.h"
#include "../game/Game.h"


// functions which can be called on collision
void teleportEntity(Entity * e1, Entity * e2, int count, int * params);

void doNothing(Entity * e1, Entity * e2, int count, int * params);

void changeColor(Entity * e1, Entity * e2, int count, int * params);

void displayDialogue(Entity * e1, Entity * e2, int count, int * params);

void battle(Entity * e1, Entity * e2, int count, int * params);

void enterLevel(Entity * e1, Entity * e2, int count, int * params);

// functions to call on move
void noMove(Entity * e, int c, int arr[2], int dt, int count, int * params);

void playerControl(Entity * e, int c, int arr[2], int dt, int count, int * params);

void randomAI(Entity * e, int c, int arr[2], int dt, int count, int * params);

#endif

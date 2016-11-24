#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <limits>
#include <sstream>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "../entities/Entities.h"
#include "../game/Game.h"
#include "typedefs.h"

extern std::ofstream LOG;
void init_logging();

//void clearScreen();

void gameLoopInputHandler(int c);

void relativeCameraPos(Entity * centerentity, Entity * drawEntity, int arr[2], int height, int width);

void splitString(std::string str_to_split, std::vector< std::string > * splits, char delimiter);

void useKeyBehaviour(Entity * e);

#endif

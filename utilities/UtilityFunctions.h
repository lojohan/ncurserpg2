#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <limits>
#include <sstream>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <ncurses.h>
#include "../entities/Entities.h"
#include "../game/Game.h"

void clearScreen();

bool kbhit();

int kbhit(int t1,int t2);

int playerInput(WINDOW *menu_win);

int playerInputBlocking(WINDOW * menu_win);

void gameLoopInputHandler(int c);

void relativeCameraPos(Entity * centerentity, Entity * drawEntity, int arr[2], int height, int width);

void splitString(std::string str_to_split, std::vector< std::string > * splits, char delimiter);

void useKeyBehaviour(Entity * e);

#endif

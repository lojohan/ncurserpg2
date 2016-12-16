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

/*
removes first occurence of t in vec.
*/
template<class T> bool removeFromVector(std::vector<T> &vec, const T &t)  {
	for (auto it = vec.begin(); it != vec.end(); it++) {
        if (*it == t) {
            vec.erase(it);
            return true;
        }
    }
    return false;
}

void gameLoopInputHandler(Input input);

void relativeCameraPos(int cx, int cy, int x, int y, int arr[2], int height, int width);
void relativeCameraPosContinuous(double cx, double cy, double x, double y, double arr[2], double height, double width);

void relativeCameraPos(Entity * centerentity, Entity * drawEntity, int arr[2], int height, int width);

void splitString(std::string str_to_split, std::vector< std::string > * splits, char delimiter);

void useKeyBehaviour(Entity * e);

#endif

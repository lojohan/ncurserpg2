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

void clearScreen();

bool kbhit();

int kbhit(int t1,int t2);

int playerInput(WINDOW *menu_win);

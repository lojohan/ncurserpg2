#ifndef MENU_H
#define MENU_H

#include "ui.h"

class Menu {

	WINDOW* menu_window;
	const char ** items;
	int nItems;
	int currentlySelectedItem;
public:

	Menu(WINDOW * window, const char * items[], int n, int selected);

	const char * getCurrentItem();
	int getCurrentItemIndex();

	bool getInput();

	void draw();

};


#endif

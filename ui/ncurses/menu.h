#ifndef MENU_H
#define MENU_H

#include "ui.h"


namespace ncursesui {

class Menu {
	NcursesUI &ui;
	WINDOW* menu_window;
	const char ** items;
	int nItems;
	int currentlySelectedItem;
public:

	Menu(NcursesUI &ui, WINDOW * window, const char * items[], int n, int selected);

	const char * getCurrentItem();
	int getCurrentItemIndex();

	bool getInput();

	void draw();

};


}// end namespace
#endif

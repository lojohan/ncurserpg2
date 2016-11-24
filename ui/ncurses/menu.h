#ifndef MENU_H
#define MENU_H

#include "ui.h"
#include <string>
#include <vector>



namespace ncursesui {

class NcursesUI;

class Menu {
	NcursesUI &ui;
	WINDOW* menu_window;
	const std::vector<std::string> &items;
	int currentlySelectedItem;
public:

	Menu(NcursesUI &ui, WINDOW * window, const std::vector<std::string> &items, int);

	const std::string getCurrentItem();
	int getCurrentItemIndex();

	bool getInput();

	void draw();

};


}// end namespace
#endif

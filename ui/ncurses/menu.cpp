#include "menu.h"

namespace ncursesui {

Menu::Menu(NcursesUI &ui, WINDOW * window, const std::vector<std::string> &items, int selected) :
		ui(ui), menu_window(window), items(items), currentlySelectedItem(selected)
{
    // ???
    keypad(menu_window,TRUE);
}

const std::string Menu::getCurrentItem(){
	return items[currentlySelectedItem];
}
int Menu::getCurrentItemIndex(){
	return currentlySelectedItem;
}

bool Menu::getInput() {
	draw();
	int ch = ui.playerInputBlocking(menu_window);
	if (ch == KEY_DOWN)
		currentlySelectedItem++;
	else if (ch == KEY_UP)
		currentlySelectedItem--;
	else if (ch == '\n') {
		return true;
	}
	currentlySelectedItem = (unsigned)currentlySelectedItem % items.size();
	draw();
	return false;
}

void Menu::draw() {
	wclear(menu_window);
	wattron(menu_window, A_STANDOUT);
	mvwprintw(menu_window, 0, 0, "What do you want to do?");
	wattroff(menu_window, A_STANDOUT);
	for (size_t i = 0, startRow = 1; i < items.size(); i++) {
		if (currentlySelectedItem == (signed)i) {
			mvwprintw(menu_window, startRow + i, 0, "> ");
			mvwprintw(menu_window, startRow + i, 2, items[i].c_str());
		} else {
			mvwprintw(menu_window, startRow + i, 0, items[i].c_str());
		}
	}
	// refresh all windows
	ui.refreshAll();
}


}

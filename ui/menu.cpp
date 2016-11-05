#include "menu.h"
#include "../game/Game.h"

Menu::Menu(WINDOW * window, const char * items[], int n, int selected) :
		menu_window(window), items(items), nItems(n), currentlySelectedItem(selected)
{

}

const char * Menu::getCurrentItem(){
	return items[currentlySelectedItem];
}
int Menu::getCurrentItemIndex(){
	return currentlySelectedItem;
}

bool Menu::getInput() {
	draw();
	int ch = playerInputBlocking(game->getGameWindow());
	if (ch == KEY_DOWN)
		currentlySelectedItem++;
	else if (ch == KEY_UP)
		currentlySelectedItem--;
	else if (ch == '\n') {
		return true;
	}
	currentlySelectedItem = (unsigned)currentlySelectedItem % nItems;
	draw();
	return false;
}

void Menu::draw() {
	wclear(menu_window);
	wattron(menu_window, A_STANDOUT);
	mvwprintw(menu_window, 0, 0, "What do you want to do?");
	wattroff(menu_window, A_STANDOUT);
	for (int i = 0, startRow = 1; i < nItems; i++) {
		if (currentlySelectedItem == i) {
			mvwprintw(menu_window, startRow + i, 0, "> ");
			mvwprintw(menu_window, startRow + i, 2, items[i]);
		} else {
			mvwprintw(menu_window, startRow + i, 0, items[i]);
		}
	}
	// refresh all windows
	game->refreshAll();
}

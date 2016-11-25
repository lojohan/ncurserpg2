/*
 * Battle.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: antolss
 */

#include "BattleView.h"



namespace ncursesui {

BattleView::BattleView(NcursesUI &ui, Game &game, Battle &battle) :
	ui(ui), game(game), battle(battle) {
	log_window = ui.getGUI1Window();
	menu_window = ui.getGUI2Window();
	main_window = ui.getGameWindow();
}

BattleView::~BattleView() {
	// TODO Auto-generated destructor stub
}

void BattleView::startBattle() {

	mvwprintw(menu_window, 0, 0, "You are under attack by ");

	wattron(menu_window, COLOR_PAIR( ui.getEntityColor(battle.getEntity2()) ));
	wprintw(menu_window, "%s", battle.getEntity2()->getName().c_str());
	wattroff(menu_window, COLOR_PAIR( ui.getEntityColor(battle.getEntity2()) ));
	wprintw(menu_window, "!");

	ui.refreshAll();

	wgetch(menu_window);
}

void BattleView::update(long dt) {
	// Clear all windows
	ui.clearAll();

	// draw battle log window
	drawBattleLog();

	// draw Main battle window
	{
		printTopParty(battle.getEntity2());
		printBottomParty(battle.getEntity1());
	}


	wclear(log_window);
	wclear(menu_window);

	// draw battle log window
	drawBattleLog();
	//mvwprintw(menu_window, 0, 0, );

	ui.refreshAll();

	//wgetch(main_window);
}

void BattleView::drawBattleLog() {
	wclear(log_window);
	for (size_t i= 0; i < battle.getBattleLog().size(); i++) {
		mvwprintw(log_window, i, 0, battle.getBattleLog().at(i).c_str());
	}
}


void BattleView::printTopParty(Entity * e) {
	int max_col,max_row;
	getmaxyx(main_window, max_row, max_col);
	mvwprintw(main_window, 0, 0, e->getName().c_str());
	int row = 2;
	int col = 0;
	for (int i = 0; i < e->getParty().size(); i++) {
		std::string name = e->getParty()[i]->getName();
		if (col + (signed)name.length() > max_col) {
			if (col == 0) {
				name.resize(max_col);
			} else {
				row += 1;
				col = 0;
			}
		}
		mvwprintw(main_window, row, col, name.c_str());
		col += name.length() + 1;
	}
}

void BattleView::printBottomParty(Entity * e) {
	int max_col,max_row;
	getmaxyx(main_window, max_row, max_col);
	mvwprintw(main_window, max_row-1, 0, e->getName().c_str());
	int row = max_row - 3;
	int col = 0;
	for (int i = 0; i < e->getParty().size(); i++) {
		std::string name = e->getParty()[i]->getName();
		if (col + (signed)name.length() > max_col) {
			if (col == 0) {
				name.resize(max_col);
			} else {
				row -= 1;
				col = 0;
			}
		}
		mvwprintw(main_window, row, col, name.c_str());
		col += name.length() + 1;
	}
}


} /* namespace ncursesui */

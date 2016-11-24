/*
 * Battle.h
 *
 *  Created on: Nov 24, 2016
 *      Author: antolss
 */

#ifndef UI_NCURSES_BATTLEVIEW_H_
#define UI_NCURSES_BATTLEVIEW_H_

#include "NcursesUI.h"
#include "../../game/Battle.h"

namespace ncursesui {

class BattleView {
	WINDOW * log_window;
	WINDOW * menu_window;
	WINDOW * main_window;

	NcursesUI &ui;
	Game &game;
	Battle &battle;

public:
	BattleView(NcursesUI &ui, Game &game, Battle &battle);
	virtual ~BattleView();

	void update(long dt);

	void startBattle();

private:

	void drawBattleLog();
	void printTopParty(Entity * e);
	void printBottomParty(Entity * e);

};

} /* namespace ncursesui */

#endif /* UI_NCURSES_BATTLEVIEW_H_ */

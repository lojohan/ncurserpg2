/*
 * NcursesUI.h
 *
 *  Created on: Nov 24, 2016
 *      Author: antolss
 */

#ifndef UI_NCURSES_NCURSESUI_H_
#define UI_NCURSES_NCURSESUI_H_

#include "ui.h"
#include "../UI.h"
#include "../../entities/entityheaders/Entity.h"
#include <ncursesw/ncurses.h>

class Game;


namespace ncursesui {

class BattleView;

class NcursesUI: public UI {
private:
	Game &game;
	BattleView * battleView;

    // should be in drawing bit
    WINDOW *super_window;
    WINDOW *title_window;

    WINDOW *game_box;
    WINDOW *game_window;

    WINDOW *gui1_box;
    WINDOW *gui1_window;

    WINDOW *gui2_box;
    WINDOW *gui2_window;

public:
    const static int GAME_HEIGHT = 15;
    const static int GAME_WIDTH = 40;

    const static int GUI1_HEIGHT = 15;
    const static int GUI1_WIDTH = 40;

    const static int GUI2_HEIGHT = 5;
    const static int GUI2_WIDTH = GAME_WIDTH + GUI1_WIDTH +2;

    const static int TITLE_HEIGHT = 2;
    const static int TITLE_WIDTH = GUI2_WIDTH + 2;

    const static int START_X = 0;
    const static int START_Y = 0;

public:
	NcursesUI(Game &game);
	virtual ~NcursesUI();

	/* Interface */
	void init();
	void update(long dt);
	int playerInput();
	void displayDialogue(Entity * e1, Entity * e2, std::string dialogue);
	void displayDebug1();
	int selectOption(const std::vector<std::string> &options);
	void startBattle(Battle &battle);

	/* Input stuff */
	int kbhit(int t1,int t2);
	int playerInput(WINDOW *menu_win);
	int playerInputBlocking(WINDOW * menu_win);

	/* Drawing stuff */
    void clearBeforeDraw(WINDOW * win, int startX, int startY, int height, int width);
    void clearGUI1();
    void clearGUI2();
    void clearGameWindow();
    void clearAll();

    void refreshGameScreen();
    void refreshGUI1();
    void refreshGUI2();
    void refreshTitle();
    void refreshAll();

    WINDOW * getGameWindow();
    WINDOW * getGUI1Window();
    WINDOW * getGUI2Window();

private:

    void drawTitle();
    void drawEntities();
    void drawEntity(WINDOW * window, Entity * e, int x, int y);
    void drawGUI1Elements();
    void drawGUI2Elements();
    void drawPause();
    void draw();

    // inits things related to ncurses (graphics)
    void initNCurses();
    void initColors();

    // creates windows and boxes.
    void createWindows();


};

}
#endif /* UI_NCURSES_NCURSESUI_H_ */

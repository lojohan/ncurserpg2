/*
 * NcursesUI.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: antolss
 */

#include "NcursesUI.h"

#include "../../game/Game.h"
#include "BattleView.h"

namespace ncursesui {

NcursesUI::NcursesUI(Game &game)
:	game(game), battleView(NULL)
{
}

NcursesUI::~NcursesUI() {
	// TODO Auto-generated destructor stub
}

void NcursesUI::init() {
	initNCurses();
}

void NcursesUI::deinit() {
    endwin();
}

void NcursesUI::startBattle(Battle &battle) {
	battleView = new BattleView(*this, game, battle);
	battleView->startBattle();
}

void NcursesUI::endBattle(Battle &battle) {
    playerInputBlocking(game_window);
    delete battleView;
	battleView = NULL;
}

void NcursesUI::update(long dt) {
	if (battleView != NULL)
	    battleView->update(dt);
	else
	    draw();
}

int NcursesUI::selectOption(const std::vector<std::string> &options) {
	int selected = 0;
	Menu menu(*this, getGUI2Window(), options, selected);
	while (!menu.getInput());
	return menu.getCurrentItemIndex();
}

void NcursesUI::drawEntities() {
    
    for(int i = Entity::BACKGROUND; i >= Entity::FOREGROUND; i--) {
        for(auto it = game.getEntities().begin(); it != game.getEntities().end(); ++it) {
            // Array containing positions of entities relative to camera.
            if( (*it)->layer == i) {
                int arr[2];
                relativeCameraPos(game.getPlayer(), *it, arr, GAME_HEIGHT, GAME_WIDTH);
                drawEntity(game_window, *it, arr[0], arr[1]);
            }
        }
    }
}

int NcursesUI::kbhit(int t1,int t2) {

    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

Input NcursesUI::playerInput() {
	switch(playerInput(this->game_window))
    {
    case KEY_UP:
        return Input::GO_UP;
	case KEY_DOWN:
	    return Input::GO_DOWN;
	case KEY_LEFT:
	    return Input::GO_LEFT;
	case KEY_RIGHT:
	    return Input::GO_RIGHT;
	// ctrl+left
	case 540:
	    return Input::TURN_LEFT;
	case 555:
	    return Input::TURN_RIGHT;
	case 561:
	    return Input::TURN_UP;
	case 520:
	    return Input::TURN_DOWN;
	case 'e':
	    return Input::USE_KEY;
	case 'p':
	    return Input::PAUSE;
	case KEY_F(1):
	    return Input::DEBUG1; 
	default:
		return Input::NONE;
	}
}
int NcursesUI::playerInput(WINDOW *menu_win) {
    nodelay(stdscr, TRUE);
    if(kbhit(1,0)) {
        return wgetch(menu_win);
    } else {
        return -1;
    }
}

int NcursesUI::playerInputBlocking(WINDOW * menu_win) {
    return wgetch(menu_win);
}

void NcursesUI::getEntityImage(Entity *e, ImageInternal &image) {
    const wchar_t * img;
    int color;
    
    switch(e->getImage().id)
    {	case 1:
        // regular wall
        img = L"#";
        color = COLOR_WHITE;
		break;
	case 2:
        // player
        img = L"\u03C3";
        color = COLOR_CYAN;
		break;
	case 3:
        // house
        img = L"\u2302";
        color = COLOR_WHITE;
	    break;
	case 4:
        // grass
        img = L"\u2591";
        color = COLOR_GREEN;
        break;
	case 5: 
	    // tree
	    img = L"\u21D1";
	    color = COLOR_GREEN;
	    break;
	case 6:
	    // brown wall
	    img = L"\u2591";
	    color = COLOR_YELLOW;
	    break;
	case 7:
	    // enemy NPC
	    img = L"\u00A2";
	    color = COLOR_RED;
	    break;
	case 8:
	    // friendly NPC
	    img = L"\u00A2";
	    color = COLOR_GREEN;
	    break;
	case 9:
	    // water
	    img = L"\u2591";
	    color = COLOR_CYAN;
	    break;
	default:
	        img = L"";
	        color = COLOR_WHITE;
		break;
    }
    
    image.img = img;
    image.color = color;
    image.id = e->getImage().id;
}

int NcursesUI::getEntityColor(Entity *e) {
    ImageInternal img;
    getEntityImage(e, img);
    return img.color;
}

void NcursesUI::drawEntity(WINDOW * window, Entity * e, int x, int y) {
    // draws the entities in list of entities with the appropriate color.
    
    ImageInternal img;
    getEntityImage(e, img);
    
    wattron(window, COLOR_PAIR( img.color ));
    mvwaddwstr(window, x, y, img.img);
    wattroff(window, COLOR_PAIR( img.color ));
}

void NcursesUI::drawPause() {
    std::string pauseString = "PAUSED";
    wattron(game_window, A_REVERSE);
    if(game.isPaused())
        mvwprintw(game_window,0,0,pauseString.c_str());
    wattroff(game_window, A_REVERSE);

}

void NcursesUI::displayDebug1(){
	clearAll();

	mvwaddwstr(getGameWindow(), 0,0,L"");
	for (int i = 1; i < 1000; i++) {
		//const wchar_t * str;
		Image image;
		//str = game->getMap()->getImageFromImageMap(&image, i);
		game.getMap()->getImageFromImageMap(&image, i);
		if (*(image.img) == '\0')
			break;
		waddwstr(getGameWindow(),image.img);
	}
	refreshAll();
	playerInput();
}

void NcursesUI::displayDialogue(Entity * e1, Entity * e2, std::string dialogue){
	clearGUI2();
	
	int color = getEntityColor(e2);

	drawEntity(getGUI2Window(), e2, 0,0);

    if (e2 != NULL) {
	    wattron(getGUI2Window(), COLOR_PAIR( color ));
	    mvwprintw(getGUI2Window(), 0, 1, " %s: ", e2->getName().c_str());
	    wattroff(getGUI2Window(), COLOR_PAIR( color ));
    }
	wprintw(getGUI2Window(), "%s",  dialogue.c_str());
	mvwprintw(getGUI2Window(), GUI2_HEIGHT-1, 0, "▼");
	refreshAll();

	int c = 0;
	while( c != '\n' && c != ' ') {
        c = playerInput(getGameWindow());
	}
}

// draw elements of GUI1
void NcursesUI::drawGUI1Elements() {
    // placeholder
    mvwprintw(gui1_window,0,0,"Currently in: ");
    mvwprintw(gui1_window,1,0,"%s", game.getCurrentZoneNameforPlayer().c_str());
    mvwprintw(gui1_window,2,0,"Current Area is friendly: %s", game.getCurrentZoneFriendly() ? "true" : "false" );
    mvwprintw(gui1_window,3,0,"Currently facing: %s", (game.getPlayer()->getCurrentDirection()).c_str() );
    mvwprintw(gui1_window,4,0,"Player position: X=%d, Y=%d", game.getPlayer()->getX(), game.getPlayer()->getY() );
    mvwprintw(gui1_window,5,0,"Game paused: %s", game.isPaused() ? "true" : "false" );
    mvwaddwstr(gui1_window,6,0,L"HP: ♥♥♥♥♥♥");

}

// draw elements of GUI2
void NcursesUI::drawGUI2Elements() {
    // placeholder
    mvwprintw(gui2_window,0,0,"Lorem Ipsum");
}

// do all the drawing.
void NcursesUI::draw() {
    clearAll();

    drawTitle();

    drawEntities();

    drawPause();

    drawGUI1Elements();
    drawGUI2Elements();

    refreshAll();
}

void NcursesUI::drawTitle() {

    std::ifstream myfile ("res/Title.txt");
//    myfile.imbue(std::locale("en_US.UTF8"));
    myfile.seekg(0, std::ios::end);
    int len = myfile.tellg();
    myfile.seekg(0);
    char title[len+1];
    if (myfile.is_open())
    {
        myfile.read(title, len);
    }

    mvwprintw(title_window,0,0,title);
}

// clears window by drawing white spaces.
void NcursesUI::clearBeforeDraw(WINDOW * win,int startX, int startY, int height, int width) {
    for(int i = startX; i < height; i++) {
        for(int j = startY; j < width; j++) {
            mvwprintw(win, i,j," ");
        }
    }
}

void NcursesUI::clearAll() {
    clearGameWindow();
    clearGUI1();
    clearGUI2();
}

void NcursesUI::clearGUI1() {
    clearBeforeDraw(gui1_window, 0, 0, GUI1_HEIGHT, GUI1_WIDTH);
}

void NcursesUI::clearGUI2() {
    clearBeforeDraw(gui2_window, 0, 0, GUI2_HEIGHT, GUI2_WIDTH);
}

void NcursesUI::clearGameWindow() {
    clearBeforeDraw(game_window, 0, 0, GAME_HEIGHT, GAME_WIDTH);
}

// refresh game_window
void NcursesUI::refreshGameScreen() {
    wrefresh(game_box);
    wrefresh(game_window);
}

// refresh gui1
void NcursesUI::refreshGUI1() {
    wrefresh(gui2_box);
    wrefresh(gui1_window);
}

// refresh gui2
void NcursesUI::refreshGUI2() {
    wrefresh(gui2_box);
    wrefresh(gui2_window);
}

// refresh title
void NcursesUI::refreshTitle() {
    wrefresh(title_window);
}

void NcursesUI::refreshAll() {
    refreshGUI1();
    refreshGUI2();
    refreshGameScreen();
    refreshTitle();

    wrefresh(super_window);
}


// inits things related to ncurses (graphics)
void NcursesUI::initNCurses() {
    setlocale(LC_ALL, "");
    initscr();

    start_color();
    initColors();

    createWindows();

    keypad(game_window,true);

    refreshAll();

    clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    curs_set(0);
}

// creates windows and boxes.
void NcursesUI::createWindows() {
    std::cout << "Creating windows";
    super_window = newwin(GAME_HEIGHT+GUI2_HEIGHT+4+TITLE_HEIGHT+1,GAME_WIDTH+4+GUI1_WIDTH,0,0);

    title_window = subwin(super_window,TITLE_HEIGHT, TITLE_WIDTH,0,0);

    game_box = subwin(super_window, GAME_HEIGHT+2,GAME_WIDTH+2,TITLE_HEIGHT,0);
    game_window = subwin(game_box, GAME_HEIGHT, GAME_WIDTH, TITLE_HEIGHT+1, 1);

    gui1_box = subwin(super_window, GUI1_HEIGHT+2, GUI1_WIDTH+2, TITLE_HEIGHT, GAME_WIDTH+2);
    gui1_window = subwin(gui1_box, GUI1_HEIGHT,GUI1_WIDTH,TITLE_HEIGHT +1,GAME_WIDTH+3);

    gui2_box = subwin(super_window, GUI2_HEIGHT+2,GUI2_WIDTH+2,TITLE_HEIGHT+ GAME_HEIGHT+2,0);
    gui2_window = subwin(gui2_box, GUI2_HEIGHT,GUI2_WIDTH,TITLE_HEIGHT + GAME_HEIGHT+3,1);

    box(game_box,0,0);
    box(gui1_box,0,0);
    box(gui2_box,0,0);

    touchwin(title_window);
    touchwin(gui1_window);
    touchwin(gui2_window);
    touchwin(game_window);
}

WINDOW * NcursesUI::getGameWindow() {
    return this->game_window;
}

WINDOW * NcursesUI::getGUI1Window() {
    return this->gui1_window;
}

WINDOW * NcursesUI::getGUI2Window() {
    return this->gui2_window;
}

// init color pairs

void NcursesUI::initColors() {
    for(int i = COLOR_RED; i <= COLOR_WHITE; i++) {
        init_pair(i, i, COLOR_BLACK);
    }
}


}

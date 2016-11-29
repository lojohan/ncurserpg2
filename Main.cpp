#include <csignal>

#include "game/Game.h"

#if BUILD_NCURSES
#	include "ui/ncurses/NcursesUI.h"
#elif BUILD_SDL
#	include "ui/sdl/SdlUi.h"
#else
#	warning UI build option not defined
#endif

using namespace std;

Game * game;

void signalHandler( int signum );

int main() {
	signal(SIGINT, signalHandler);

    game = new Game();
    UI* ui = NULL;
#if BUILD_NCURSES
    ui = new ncursesui::NcursesUI(*game);
#elif BUILD_SDL
    ui = new sdlui::SdlUi(*game);
#endif
    game->setUI(ui);
    game->start();
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";

   // cleanup and close up stuff here
   game->end();

   // terminate program
   exit(signum);

}

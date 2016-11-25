#include "game/Game.h"
#include "ui/ncurses/NcursesUI.h"

using namespace std;

Game * game;

int main() {
    game = new Game();
    game->setUI(new ncursesui::NcursesUI(*game));
    game->start();
}

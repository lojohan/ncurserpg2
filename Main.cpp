#include "game/Game.h"

using namespace std;

Game * game;

int main() {
    game = new Game();
    game->start();
}

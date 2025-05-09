#include "Game.h"
#include <tchar.h>

using namespace sf;

int main() {
    Game game;
    game.run();  // En lugar de game.Loop();
    return 0;
}
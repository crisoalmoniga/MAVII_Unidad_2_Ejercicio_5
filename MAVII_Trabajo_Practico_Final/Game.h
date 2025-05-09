#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Counter.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    enum GameState { MENU, PLAYING, GAME_OVER };
    GameState state;

    sf::RenderWindow window;
    Menu* menu;
    Counter* counter;
};

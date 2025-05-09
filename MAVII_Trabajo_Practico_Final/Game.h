#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include "Ragdoll.h"
#include "Cannon.h"
#include "Counter.h"
#include "Menu.h"

enum GameState { MENU, PLAYING };

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    GameState state;
    int contador;

    std::unique_ptr<Cannon> cannon;
    std::unique_ptr<Counter> counter;
    std::unique_ptr<Menu> menu;
    b2World world;
    std::vector<Ragdoll> ragdolls;
};

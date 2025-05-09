#pragma once
#include <SFML/Graphics.hpp>
#include "D:/Universidad - Cris/Videojuegos/Universidad del Litoral/MAV2/2025/MAVII2025_Trabajo_practico_final/MAVII2025_Trabajo_practico_final/EsqueletoAPP/Box2dFirstApp/Build/Header Files/Level.h"
#include "D:/Universidad - Cris/Videojuegos/Universidad del Litoral/MAV2/2025/MAVII2025_Trabajo_practico_final/MAVII2025_Trabajo_practico_final/EsqueletoAPP/Box2dFirstApp/Build/Header Files/Menu.h"
#include "D:/Universidad - Cris/Videojuegos/Universidad del Litoral/MAV2/2025/MAVII2025_Trabajo_practico_final/MAVII2025_Trabajo_practico_final/EsqueletoAPP/Box2dFirstApp/Build/Header Files/Counter.h"



class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Level* currentLevel;
    Menu* menu;
    Counter* counter;

    enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };
    GameState state;
};
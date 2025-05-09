#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "TP Final MAVII"), state(MENU) {
    menu = new Menu(window);
    counter = new Counter();
    currentLevel = nullptr;  // Se inicializa en el menú
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    switch (state) {
    case MENU:
        if (menu->isStartPressed()) {
            state = PLAYING;
            currentLevel = new Level1();  // Arranca en el nivel 1
        }
        break;

    case PLAYING:
        if (currentLevel) currentLevel->update();
        counter->update();
        break;

    case PAUSED:
        // Lógica de pausa
        break;

    case GAME_OVER:
        // Lógica de fin de juego
        break;
    }
}

void Game::render() {
    window.clear();
    switch (state) {
    case MENU:
        menu->draw(window);
        break;

    case PLAYING:
        if (currentLevel) currentLevel->render(window);
        counter->draw(window);
        break;

    case PAUSED:
        // Renderizar menú de pausa
        break;

    case GAME_OVER:
        // Renderizar pantalla de fin de juego
        break;
    }
    window.display();
}
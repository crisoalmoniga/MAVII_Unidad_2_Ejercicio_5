#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "TP Final MAVII"), state(MENU) {
    menu = new Menu(window);
    counter = new Counter();
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

        if (state == MENU && menu->isStartPressed()) {
            state = PLAYING;
            counter->reset();
        }
    }
}

void Game::update() {
    if (state == PLAYING) {
        counter->update();
        // Aquí irá la lógica del nivel actual
    }
}

void Game::render() {
    window.clear();
    if (state == MENU) {
        menu->draw(window);
    }
    else if (state == PLAYING) {
        counter->draw(window);
        // Aquí dibujaremos el nivel actual
    }
    window.display();
}

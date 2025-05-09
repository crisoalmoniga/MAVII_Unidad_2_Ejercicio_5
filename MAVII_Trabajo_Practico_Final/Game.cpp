#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

Game::Game()
    : window(sf::VideoMode(800, 600), "TP Final MAVII"),
    state(MENU),
    contador(0),
    world(b2Vec2(0.0f, 9.8f))  // Gravedad hacia abajo
{
    menu = std::make_unique<Menu>(window);
    cannon = std::make_unique<Cannon>(sf::Vector2f(100, 500));
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (state == MENU && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            state = PLAYING;
        }

        if (state == PLAYING && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            float angle = std::atan2(mousePos.y - 500, mousePos.x - 100);
            float power = std::sqrt(std::pow(mousePos.x - 100, 2) + std::pow(mousePos.y - 500, 2));
            cannon->shoot(world, ragdolls, angle, power);
            counter->increment();
        }
    }
}

void Game::update() {
    world.Step(1.0f / 60.0f, 8, 3);  // Simulación física

    for (auto& ragdoll : ragdolls) {
        ragdoll.update();
    }
}

void Game::render() {
    window.clear();
    menu->draw(window);

    cannon->draw(window);

    for (auto& ragdoll : ragdolls) {
        ragdoll.draw(window);
    }

    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}
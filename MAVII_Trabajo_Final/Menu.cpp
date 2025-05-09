#include "Menu.h"

Menu::Menu() {
    font.loadFromFile("assets/GAME_glm.ttf");

    title.setFont(font);
    title.setString("TP Final MAVII");
    title.setCharacterSize(60);
    title.setPosition(200, 100);

    startText.setFont(font);
    startText.setString("Presiona ENTER para comenzar");
    startText.setCharacterSize(30);
    startText.setPosition(180, 250);

    exitText.setFont(font);
    exitText.setString("Presiona ESC para salir");
    exitText.setCharacterSize(30);
    exitText.setPosition(180, 350);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(startText);
    window.draw(exitText);
}

bool Menu::isStartPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}

bool Menu::isExitPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}
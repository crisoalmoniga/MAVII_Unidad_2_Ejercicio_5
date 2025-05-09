#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : startPressed(false) {
    font.loadFromFile("assets/GAME_glm.ttf");

    title.setFont(font);
    title.setString("TP Final MAVII");
    title.setCharacterSize(48);
    title.setPosition(200, 100);

    startText.setFont(font);
    startText.setString("Presiona ENTER para empezar");
    startText.setCharacterSize(24);
    startText.setPosition(200, 300);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(startText);
}

bool Menu::isStartPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}

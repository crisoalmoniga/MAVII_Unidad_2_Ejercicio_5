#include "HUD.h"

HUD::HUD() {
    font.loadFromFile("assets/GAME_glm.ttf");

    shotsText.setFont(font);
    shotsText.setCharacterSize(20);
    shotsText.setPosition(10, 10);

    angleText.setFont(font);
    angleText.setCharacterSize(20);
    angleText.setPosition(10, 40);

    powerText.setFont(font);
    powerText.setCharacterSize(20);
    powerText.setPosition(10, 70);
}

void HUD::update(int shots, float angle, float power) {
    shotsText.setString("Disparos: " + std::to_string(shots));
    angleText.setString("Angulo: " + std::to_string(static_cast<int>(angle)));
    powerText.setString("Potencia: " + std::to_string(static_cast<int>(power)));
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(shotsText);
    window.draw(angleText);
    window.draw(powerText);
}

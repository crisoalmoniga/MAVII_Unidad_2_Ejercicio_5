#include "HUD.h"

// Constructor
HUD::HUD() {}

// Inicialización del HUD
void HUD::initialize(sf::Font& font) {
    shotsText.setFont(font);
    shotsText.setCharacterSize(20);
    shotsText.setPosition(10, 10);
    shotsText.setFillColor(sf::Color::Yellow);

    angleText.setFont(font);
    angleText.setCharacterSize(20);
    angleText.setPosition(10, 40);
    angleText.setFillColor(sf::Color::Yellow);

    powerText.setFont(font);
    powerText.setCharacterSize(20);
    powerText.setPosition(10, 70);
    powerText.setFillColor(sf::Color::Yellow);
}

// Actualización del HUD con datos actuales
void HUD::update(int shotCount, float angle, float power) {
    shotsText.setString("Disparos: " + std::to_string(shotCount));
    angleText.setString("Ángulo: " + std::to_string(static_cast<int>(angle * 180 / 3.14159f)));
    powerText.setString("Potencia: " + std::to_string(static_cast<int>(power)));
}

// Dibujar el HUD en la pantalla
void HUD::draw(sf::RenderWindow& window) {
    window.draw(shotsText);
    window.draw(angleText);
    window.draw(powerText);
}

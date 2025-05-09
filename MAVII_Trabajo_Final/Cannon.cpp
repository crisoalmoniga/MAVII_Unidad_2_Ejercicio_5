#include "Cannon.h"
#include <cmath>

// Constructor del cañón
Cannon::Cannon(sf::Vector2f position) : position(position), power(0.f), angle(0.f) {
    // Inicializar la línea de disparo
    shotLine[0].color = sf::Color::Red;
    shotLine[1].color = sf::Color::Red;
}

// Actualización del cañón según la posición del mouse
void Cannon::update(sf::RenderWindow& window, const sf::Vector2f& mousePosition) {
    sf::Vector2f dir = mousePosition - position;
    power = std::min(std::sqrt(dir.x * dir.x + dir.y * dir.y), 150.f);
    angle = std::atan2(dir.y, dir.x);

    // Actualizar la línea de disparo
    shotLine[0].position = position;
    shotLine[1].position = position + sf::Vector2f(std::cos(angle), std::sin(angle)) * power;
}

// Dibujo del cañón en pantalla
void Cannon::draw(sf::RenderWindow& window) {
    window.draw(shotLine, 2, sf::Lines);
}

// Obtener el ángulo del cañón
float Cannon::getAngle() const {
    return angle;
}

// Obtener la potencia de disparo
float Cannon::getPower() const {
    return power;
}

// Obtener la posición del cañón
sf::Vector2f Cannon::getPosition() const {
    return position;
}

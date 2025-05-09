#include "Cannon.h"
#include <cmath>

// Constructor del ca��n
Cannon::Cannon(sf::Vector2f position) : position(position), power(0.f), angle(0.f) {
    // Inicializar la l�nea de disparo
    shotLine[0].color = sf::Color::Red;
    shotLine[1].color = sf::Color::Red;
}

// Actualizaci�n del ca��n seg�n la posici�n del mouse
void Cannon::update(sf::RenderWindow& window, const sf::Vector2f& mousePosition) {
    sf::Vector2f dir = mousePosition - position;
    power = std::min(std::sqrt(dir.x * dir.x + dir.y * dir.y), 150.f);
    angle = std::atan2(dir.y, dir.x);

    // Actualizar la l�nea de disparo
    shotLine[0].position = position;
    shotLine[1].position = position + sf::Vector2f(std::cos(angle), std::sin(angle)) * power;
}

// Dibujo del ca��n en pantalla
void Cannon::draw(sf::RenderWindow& window) {
    window.draw(shotLine, 2, sf::Lines);
}

// Obtener el �ngulo del ca��n
float Cannon::getAngle() const {
    return angle;
}

// Obtener la potencia de disparo
float Cannon::getPower() const {
    return power;
}

// Obtener la posici�n del ca��n
sf::Vector2f Cannon::getPosition() const {
    return position;
}

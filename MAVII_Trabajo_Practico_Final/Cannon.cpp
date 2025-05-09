#include "Cannon.h"
#include "Ragdoll.h"
#include <cmath>

Cannon::Cannon(sf::Vector2f position) : position(position), angle(0) {
    barrel.setSize(sf::Vector2f(50, 10));
    barrel.setFillColor(sf::Color::Red);
    barrel.setOrigin(0, 5);
}

void Cannon::update(sf::Vector2f mousePos) {
    sf::Vector2f dir = mousePos - position;
    angle = std::atan2(dir.y, dir.x) * 180 / 3.14159f;
    barrel.setPosition(position);
    barrel.setRotation(angle);
}

void Cannon::shoot(b2World& world, std::vector<Ragdoll>& ragdolls, float angle, float potencia) {
    float radianes = angle * 3.14159f / 180;
    sf::Vector2f direction(std::cos(radianes), std::sin(radianes));
    Ragdoll newRagdoll(world, position, angle, potencia);
    ragdolls.push_back(std::move(newRagdoll));
}

void Cannon::draw(sf::RenderWindow& window) {
    window.draw(barrel);
}
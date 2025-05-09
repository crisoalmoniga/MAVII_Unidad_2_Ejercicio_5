#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Ragdoll.h"
#include <box2d/box2d.h>

class Cannon {
public:
    Cannon(sf::Vector2f position);
    void update(sf::Vector2f mousePos);
    void shoot(b2World& world, std::vector<Ragdoll>& ragdolls, float angle, float potencia);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    sf::RectangleShape barrel;
    float angle;
};

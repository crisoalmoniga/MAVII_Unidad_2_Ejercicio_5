#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class ParteCuerpo {
public:
    ParteCuerpo(b2World& world, float x, float y, float ancho, float alto);
    void update();
    void draw(sf::RenderWindow& window);

    b2Body* getBody() const { return body; }

private:
    sf::RectangleShape shape;
    b2Body* body;
};


#ifndef CANNON_H
#define CANNON_H

#include <SFML/Graphics.hpp>

class Cannon {
public:
    Cannon(sf::Vector2f position);
    void update(sf::RenderWindow& window, const sf::Vector2f& mousePosition);
    void draw(sf::RenderWindow& window);
    float getAngle() const;
    float getPower() const;
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f position;
    float power;
    float angle;
    sf::Vertex shotLine[2];
};

#endif

#ifndef BOXWALL_H
#define BOXWALL_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <memory>

class BoxWall {
public:
    BoxWall(b2World& world, int rows, int cols, float startX, float startY);
    void draw(sf::RenderWindow& window);
    bool isCleared() const;

private:
    std::vector<std::unique_ptr<sf::RectangleShape>> boxShapes;
    std::vector<b2Body*> boxBodies;
};

#endif

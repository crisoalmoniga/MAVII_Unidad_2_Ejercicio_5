#pragma once
#include <SFML/Graphics.hpp>

class Counter {
public:
    Counter();
    void update();
    void draw(sf::RenderWindow& window);
    void increment();
    void reset();
    int getCount() const;

private:
    int count;
    sf::Font font;
    sf::Text text;
};

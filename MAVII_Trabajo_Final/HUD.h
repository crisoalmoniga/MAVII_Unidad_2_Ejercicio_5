#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD();
    void update(int shots, float angle, float power);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text shotsText;
    sf::Text angleText;
    sf::Text powerText;
};

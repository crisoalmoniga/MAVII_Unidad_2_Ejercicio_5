#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class HUD {
public:
    HUD();
    void initialize(sf::Font& font);
    void update(int shotCount, float angle, float power);
    void draw(sf::RenderWindow& window);

private:
    sf::Text shotsText;
    sf::Text angleText;
    sf::Text powerText;
};

#endif

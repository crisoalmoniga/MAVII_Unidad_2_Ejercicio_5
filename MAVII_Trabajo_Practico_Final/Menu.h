#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isStartPressed() const;

private:
    sf::Font font;
    sf::Text title;
    sf::Text startText;
    bool startPressed;
};

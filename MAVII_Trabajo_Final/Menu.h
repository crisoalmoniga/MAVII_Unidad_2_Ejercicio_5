#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu();
    void draw(sf::RenderWindow& window);
    bool isStartPressed() const;
    bool isExitPressed() const;

private:
    sf::Font font;
    sf::Text title;
    sf::Text startText;
    sf::Text exitText;
};

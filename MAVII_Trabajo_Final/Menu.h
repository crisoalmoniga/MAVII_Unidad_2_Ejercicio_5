#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu();
    void initialize(sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isStartPressed() const;
    bool isExitPressed() const;
    void setTitle(const std::string& newTitle);
    void setStartText(const std::string& newText);


private:
    sf::Text title;
    sf::Text startText;
    sf::Text exitText;
};

#endif

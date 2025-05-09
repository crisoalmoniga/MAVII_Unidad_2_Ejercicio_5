#include "Counter.h"

Counter::Counter() : count(0) {
    font.loadFromFile("assets/GAME_glm.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setPosition(10, 10);
    text.setString("Disparos: 0");
}

void Counter::update() {
    text.setString("Disparos: " + std::to_string(count));
}

void Counter::draw(sf::RenderWindow& window) {
    window.draw(text);
}

void Counter::increment() {
    ++count;
}

void Counter::reset() {
    count = 0;
}

int Counter::getCount() const {
    return count;
}

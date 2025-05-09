#include "Menu.h"

// Constructor del men�
Menu::Menu() {}

// Inicializaci�n del men�
void Menu::initialize(sf::Font& font) {
    // T�tulo del juego
    title.setFont(font);
    title.setString("TP - Ragdoll Cannon");
    title.setCharacterSize(60);
    title.setPosition(100, 100);
    title.setFillColor(sf::Color::White);

    // Texto para iniciar el juego
    startText.setFont(font);
    startText.setString("Presiona ENTER para comenzar");
    startText.setCharacterSize(30);
    startText.setPosition(100, 250);
    startText.setFillColor(sf::Color::White);

    // Texto para salir del juego
    exitText.setFont(font);
    exitText.setString("Presiona ESC para salir");
    exitText.setCharacterSize(30);
    exitText.setPosition(100, 350);
    exitText.setFillColor(sf::Color::White);
}

// Dibujar el men� en pantalla
void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(startText);
    window.draw(exitText);
}

// Verificar si el jugador presion� ENTER para iniciar el juego
bool Menu::isStartPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}

// Verificar si el jugador presion� ESC para salir del juego
bool Menu::isExitPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

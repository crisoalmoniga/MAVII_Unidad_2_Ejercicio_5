#include "Menu.h"

// Constructor del men� principal
Menu::Menu() {
    // Cargar la fuente desde el archivo
    font.loadFromFile("assets/GAME_glm.ttf");

    // Configuraci�n del t�tulo del men�
    title.setFont(font);                              // Asigna la fuente al texto
    title.setString("TP Final MAVII");                  // Texto que se muestra en el t�tulo
    title.setCharacterSize(60);                        // Tama�o de la fuente
    title.setPosition(200, 100);                       // Posici�n en la ventana

    // Configuraci�n del texto de inicio
    startText.setFont(font);                           // Asigna la fuente al texto
    startText.setString("Presiona ENTER para comenzar"); // Instrucci�n para iniciar el juego
    startText.setCharacterSize(30);                     // Tama�o de la fuente
    startText.setPosition(180, 250);                    // Posici�n en la ventana

    // Configuraci�n del texto de salida
    exitText.setFont(font);                            // Asigna la fuente al texto
    exitText.setString("Presiona ESC para salir");       // Instrucci�n para salir del juego
    exitText.setCharacterSize(30);                      // Tama�o de la fuente
    exitText.setPosition(180, 350);                     // Posici�n en la ventana
}

// M�todo para dibujar el men� en la pantalla
void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);       // Dibuja el t�tulo del men�
    window.draw(startText);   // Dibuja el texto de inicio
    window.draw(exitText);    // Dibuja el texto de salida
}

// Verifica si se ha presionado la tecla ENTER para iniciar el juego
bool Menu::isStartPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
}

// Verifica si se ha presionado la tecla ESC para salir del juego
bool Menu::isExitPressed() const {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}
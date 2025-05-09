#include "Menu.h"

// Constructor del menú principal
Menu::Menu() {
    // Cargar la fuente desde el archivo
    font.loadFromFile("assets/GAME_glm.ttf");

    // Configuración del título del menú
    title.setFont(font);                              // Asigna la fuente al texto
    title.setString("TP Final MAVII");                  // Texto que se muestra en el título
    title.setCharacterSize(60);                        // Tamaño de la fuente
    title.setPosition(200, 100);                       // Posición en la ventana

    // Configuración del texto de inicio
    startText.setFont(font);                           // Asigna la fuente al texto
    startText.setString("Presiona ENTER para comenzar"); // Instrucción para iniciar el juego
    startText.setCharacterSize(30);                     // Tamaño de la fuente
    startText.setPosition(180, 250);                    // Posición en la ventana

    // Configuración del texto de salida
    exitText.setFont(font);                            // Asigna la fuente al texto
    exitText.setString("Presiona ESC para salir");       // Instrucción para salir del juego
    exitText.setCharacterSize(30);                      // Tamaño de la fuente
    exitText.setPosition(180, 350);                     // Posición en la ventana
}

// Método para dibujar el menú en la pantalla
void Menu::draw(sf::RenderWindow& window) {
    window.draw(title);       // Dibuja el título del menú
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
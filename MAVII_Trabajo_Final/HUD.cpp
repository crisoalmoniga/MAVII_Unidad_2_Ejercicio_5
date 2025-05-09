#include "HUD.h"

// Constructor del HUD
HUD::HUD() {
    // Carga la fuente desde el archivo especificado
    font.loadFromFile("assets/GAME_glm.ttf");

    // Configuraci�n del texto que muestra la cantidad de disparos
    shotsText.setFont(font);               // Asigna la fuente al texto
    shotsText.setCharacterSize(20);         // Tama�o de la fuente
    shotsText.setPosition(10, 10);          // Posici�n en la pantalla

    // Configuraci�n del texto que muestra el �ngulo de disparo
    angleText.setFont(font);                // Asigna la fuente al texto
    angleText.setCharacterSize(20);          // Tama�o de la fuente
    angleText.setPosition(10, 40);           // Posici�n en la pantalla

    // Configuraci�n del texto que muestra la potencia de disparo
    powerText.setFont(font);                // Asigna la fuente al texto
    powerText.setCharacterSize(20);          // Tama�o de la fuente
    powerText.setPosition(10, 70);           // Posici�n en la pantalla
}

// Actualizaci�n de los valores del HUD
void HUD::update(int shots, float angle, float power) {
    // Actualiza el texto con la cantidad de disparos
    shotsText.setString("Disparos: " + std::to_string(shots));

    // Actualiza el texto con el �ngulo de disparo (convertido a entero para mejor presentaci�n)
    angleText.setString("Angulo: " + std::to_string(static_cast<int>(angle)));

    // Actualiza el texto con la potencia de disparo (convertido a entero para mejor presentaci�n)
    powerText.setString("Potencia: " + std::to_string(static_cast<int>(power)));
}

// Dibuja el HUD en la ventana proporcionada
void HUD::draw(sf::RenderWindow& window) {
    window.draw(shotsText);   // Dibuja el contador de disparos
    window.draw(angleText);   // Dibuja el �ngulo de disparo
    window.draw(powerText);   // Dibuja la potencia de disparo
}
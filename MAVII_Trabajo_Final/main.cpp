#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "ParteCuerpo.h"
#include "Ragdoll.h"
#include "Cannon.h"
#include "HUD.h"
#include "Menu.h"
#include "BoxWall.h"
#include <list>
#include <vector>
#include <memory>
#include <cmath>

// Factor de escala para transformar coordenadas físicas a píxeles
#define SCALE 100.0f

// Definición de los estados del juego
enum GameState { MENU, PLAYING };
GameState state = MENU;

// Contador global de disparos
int shotCount = 0;

// Crear el objeto HUD
HUD hud;

// Crear el objeto Menú
Menu menu;

int main() {
    // Creación de la ventana principal
    sf::RenderWindow window(sf::VideoMode(800, 600), "TP - Ragdoll Cannon");
    window.setFramerateLimit(60);

    // Mundo físico con gravedad
    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    // Cargar la fuente
    sf::Font font;
    font.loadFromFile("assets/GAME_glm.ttf");

    // Inicializar el HUD y el menú
    hud.initialize(font);
    menu.initialize(font);

    // Lista que almacena los ragdolls disparados
    std::list<Ragdoll> ragdolls;

    // Crear el objeto cañón
    Cannon cannon(sf::Vector2f(100.f, 500.f));

    // Crear la pared de cajas
    BoxWall boxWall(world, 5, 3, 600.f, 500.f); // 5 filas, 3 columnas

    // Definición del piso y límites del mundo
    b2BodyDef groundDef;
    groundDef.position.Set(0.f, 0.f);
    b2Body* ground = world.CreateBody(&groundDef);

    b2EdgeShape edge;
    edge.SetTwoSided(b2Vec2(0, 6), b2Vec2(8, 6));
    ground->CreateFixture(&edge, 0.0f);
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(8, 0));
    ground->CreateFixture(&edge, 0.0f);
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, 6));
    ground->CreateFixture(&edge, 0.0f);
    edge.SetTwoSided(b2Vec2(8, 0), b2Vec2(8, 6));
    ground->CreateFixture(&edge, 0.0f);

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Control del menú
            if (state == MENU) {
                if (menu.isStartPressed()) {
                    state = PLAYING;
                }
                else if (menu.isExitPressed()) {
                    window.close();
                }
            }
            // Control durante el juego
            else if (state == PLAYING) {
                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePos);
                    cannon.update(window, mouseWorld);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    ragdolls.emplace_back(world, cannon.getPosition(), cannon.getAngle(), cannon.getPower());
                    shotCount++;
                    hud.update(shotCount, cannon.getAngle(), cannon.getPower());
                }

                // Verificar si el nivel está completo (todas las cajas caídas)
                if (boxWall.isCleared()) {
                    state = MENU;
                    menu.setTitle("¡Nivel Completado!");
                    menu.setStartText("Presiona ENTER para el siguiente nivel");
                }

            }
        }

        // Actualización del mundo físico
        world.Step(1.f / 60.f, 8, 3);
        window.clear();

        // Renderizado del menú
        if (state == MENU) {
            menu.draw(window);
        }
        // Renderizado durante el juego
        else if (state == PLAYING) {
            // Dibujar el cañón
            cannon.draw(window);

            // Dibujar los ragdolls en pantalla
            for (auto& ragdoll : ragdolls)
                ragdoll.draw(window);

            // Dibujar la pared de cajas
            boxWall.draw(window);

            // Dibujar el HUD
            hud.draw(window);
        }

        // Actualizar la pantalla
        window.display();
    }

    return 0;
}
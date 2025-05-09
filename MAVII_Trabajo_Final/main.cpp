#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "ParteCuerpo.h"
#include "Ragdoll.h"
#include <list>
#include <vector>
#include <memory>
#include <cmath>

// Factor de escala para transformar coordenadas f�sicas a p�xeles
#define SCALE 100.0f

// Definici�n de los estados del juego
enum GameState { MENU, PLAYING };
GameState state = MENU;

// Variables globales para el men�
sf::Font font;
sf::Text title;
sf::Text startText;
sf::Text exitText;

// Variables para el HUD (Interfaz gr�fica)
sf::Text shotsText;
sf::Text angleText;
sf::Text powerText;
int shotCount = 0;

// Inicializaci�n del men�
void initializeMenu() {
    // Carga la fuente para el texto del men�
    font.loadFromFile("assets/GAME_glm.ttf");

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

// Inicializaci�n del HUD (Heads-Up Display)
void initializeHUD() {
    shotsText.setFont(font);
    shotsText.setCharacterSize(20);
    shotsText.setPosition(10, 10);
    shotsText.setFillColor(sf::Color::Yellow);

    angleText.setFont(font);
    angleText.setCharacterSize(20);
    angleText.setPosition(10, 40);
    angleText.setFillColor(sf::Color::Yellow);

    powerText.setFont(font);
    powerText.setCharacterSize(20);
    powerText.setPosition(10, 70);
    powerText.setFillColor(sf::Color::Yellow);
}

// Actualizaci�n del HUD con datos actuales
void updateHUD(float angle, float power) {
    shotsText.setString("Disparos: " + std::to_string(shotCount));
    angleText.setString("�ngulo: " + std::to_string(static_cast<int>(angle * 180 / 3.14159f)));
    powerText.setString("Potencia: " + std::to_string(static_cast<int>(power)));
}

int main() {
    // Creaci�n de la ventana principal
    sf::RenderWindow window(sf::VideoMode(800, 600), "TP - Ragdoll Cannon");
    window.setFramerateLimit(60);

    // Mundo f�sico con gravedad
    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    // Inicializaci�n del men� y el HUD
    initializeMenu();
    initializeHUD();

    // Definici�n del piso y l�mites del mundo
    b2BodyDef groundDef;
    groundDef.position.Set(0.f, 0.f);
    b2Body* ground = world.CreateBody(&groundDef);

    b2EdgeShape edge;

    // Piso del mundo
    edge.SetTwoSided(b2Vec2(0, 6), b2Vec2(8, 6));
    ground->CreateFixture(&edge, 0.0f);

    // Techo (parte superior)
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(8, 0));
    ground->CreateFixture(&edge, 0.0f);

    // Pared izquierda
    edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, 6));
    ground->CreateFixture(&edge, 0.0f);

    // Pared derecha
    edge.SetTwoSided(b2Vec2(8, 0), b2Vec2(8, 6));
    ground->CreateFixture(&edge, 0.0f);

    // Lista que almacena los ragdolls disparados
    std::list<Ragdoll> ragdolls;

    // Par�metros del ca��n
    sf::Vector2f cannonPos(100.f, 500.f);
    sf::Vector2f mouseWorld = cannonPos;
    float currentPower = 0.f;
    float cannonAngle = 0.f;

    // L�nea que indica la direcci�n del disparo
    sf::Vertex shotLine[2];
    shotLine[0].color = sf::Color::Red;
    shotLine[1].color = sf::Color::Red;

    // Plataforma oscilante (balanza)
    b2Body* pivot;    // Pivote central
    b2Body* platform; // Plataforma m�vil

    // Crear el pivote est�tico en el centro de la pantalla
    b2BodyDef pivotDef;
    pivotDef.position.Set(4.0f, 3.0f); // Posici�n centrada en la pantalla
    pivot = world.CreateBody(&pivotDef);

    // Forma del pivote (punto peque�o)
    b2CircleShape pivotShape;
    pivotShape.m_radius = 0.1f;

    // Fixture del pivote
    b2FixtureDef pivotFixture;
    pivotFixture.shape = &pivotShape;
    pivotFixture.density = 1.0f;
    pivot->CreateFixture(&pivotFixture);

    // Crear la plataforma din�mica
    b2BodyDef platformDef;
    platformDef.type = b2_dynamicBody;
    platformDef.position.Set(4.0f, 3.0f); // Mismo punto que el pivote
    platform = world.CreateBody(&platformDef);

    // Forma de la plataforma (barra horizontal)
    b2PolygonShape platformShape;
    platformShape.SetAsBox(2.0f, 0.1f); // Ancho y altura de la barra

    // Fixture de la plataforma
    b2FixtureDef platformFixture;
    platformFixture.shape = &platformShape;
    platformFixture.density = 2.0f;    // Suficiente peso para oscilar
    platformFixture.friction = 0.5f;
    platform->CreateFixture(&platformFixture);

    // Crear el Revolute Joint para permitir la oscilaci�n
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = pivot;
    jointDef.bodyB = platform;
    jointDef.localAnchorA.Set(0.0f, 0.0f); // Centro del pivote
    jointDef.localAnchorB.Set(0.0f, 0.0f); // Centro de la plataforma
    jointDef.collideConnected = false;     // Sin colisi�n entre pivot y plataforma

    // Limitar el �ngulo de oscilaci�n
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -0.25f * b2_pi;  // �ngulo m�nimo (en radianes)
    jointDef.upperAngle = 0.25f * b2_pi;   // �ngulo m�ximo (en radianes)

    // Crear el joint en el mundo f�sico
    world.CreateJoint(&jointDef);

    // Representaci�n visual de la plataforma en SFML
    sf::RectangleShape platformVisual(sf::Vector2f(400, 20));
    platformVisual.setOrigin(200, 10);        // Centro de rotaci�n
    platformVisual.setFillColor(sf::Color(139, 69, 19)); // Color madera

    // Crear la carga sobre la plataforma (bloque peque�o)
    b2Body* carga;
    b2BodyDef cargaDef;
    cargaDef.type = b2_dynamicBody;
    cargaDef.position.Set(4.0f, 2.8f); // Posici�n sobre la plataforma
    carga = world.CreateBody(&cargaDef);

    b2PolygonShape cargaShape;
    cargaShape.SetAsBox(0.2f, 0.2f); // Tama�o del bloque

    b2FixtureDef cargaFixture;
    cargaFixture.shape = &cargaShape;
    cargaFixture.density = 1.0f;
    cargaFixture.friction = 0.3f;
    carga->CreateFixture(&cargaFixture);

    // Visualizaci�n de la carga en SFML
    sf::RectangleShape cargaVisual(sf::Vector2f(40, 40));
    cargaVisual.setOrigin(20, 20);
    cargaVisual.setFillColor(sf::Color::Red);



    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Control del men�
            if (state == MENU) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    state = PLAYING;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }
            // Control durante el juego
            else if (state == PLAYING) {
                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    mouseWorld = window.mapPixelToCoords(mousePos);
                    sf::Vector2f dir = mouseWorld - cannonPos;
                    currentPower = std::min(std::sqrt(dir.x * dir.x + dir.y * dir.y), 150.f);
                    cannonAngle = std::atan2(dir.y, dir.x);
                    updateHUD(cannonAngle, currentPower);
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    ragdolls.emplace_back(world, cannonPos, cannonAngle, currentPower);
                    shotCount++;
                    updateHUD(cannonAngle, currentPower);
                }
                // Verificar si la carga toca el suelo (nivel completado)
                b2Vec2 cargaPos = carga->GetPosition();
                if (cargaPos.y * SCALE >= 600) {
                    state = MENU;
                    title.setString("�Nivel Completado!");
                    startText.setString("Presiona ENTER para el siguiente nivel");
                }

            }
        }

        // Actualizaci�n del mundo f�sico
        world.Step(1.f / 60.f, 8, 3);
        window.clear();

        // Renderizado del men�
        if (state == MENU) {
            window.draw(title);
            window.draw(startText);
            window.draw(exitText);
        }
        // Renderizado durante el juego
        else if (state == PLAYING) {
            shotLine[0].position = cannonPos;
            shotLine[1].position = cannonPos + sf::Vector2f(std::cos(cannonAngle), std::sin(cannonAngle)) * currentPower;
            window.draw(shotLine, 2, sf::Lines);

            // Dibuja todos los ragdolls en pantalla
            for (auto& ragdoll : ragdolls)
                ragdoll.draw(window);

            // Dibuja el HUD
            window.draw(shotsText);
            window.draw(angleText);
            window.draw(powerText);
        }

        // Actualizar posici�n y rotaci�n de la plataforma visual
        b2Vec2 platformPos = platform->GetPosition();
        float platformAngle = platform->GetAngle();
        platformVisual.setPosition(platformPos.x * SCALE, platformPos.y * SCALE);
        platformVisual.setRotation(platformAngle * 180 / b2_pi);

        // Dibujar la plataforma oscilante en la ventana
        window.draw(platformVisual);


        // Actualiza la pantalla
        window.display();
    }

    return 0;
}
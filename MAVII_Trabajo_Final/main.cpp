#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "ParteCuerpo.h"
#include "Ragdoll.h"
#include <list>
#include <vector>
#include <memory>
#include <cmath>

#define SCALE 100.0f

// Estado del juego
enum GameState { MENU, PLAYING };
GameState state = MENU;

// Menú de inicio
sf::Font font;
sf::Text title;
sf::Text startText;
sf::Text exitText;

// HUD
sf::Text shotsText;
sf::Text angleText;
sf::Text powerText;
int shotCount = 0;

void initializeMenu() {
    font.loadFromFile("assets/GAME_glm.ttf");

    title.setFont(font);
    title.setString("TP - Ragdoll Cannon");
    title.setCharacterSize(60);
    title.setPosition(100, 100);
    title.setFillColor(sf::Color::White);

    startText.setFont(font);
    startText.setString("Presiona ENTER para comenzar");
    startText.setCharacterSize(30);
    startText.setPosition(100, 250);
    startText.setFillColor(sf::Color::White);

    exitText.setFont(font);
    exitText.setString("Presiona ESC para salir");
    exitText.setCharacterSize(30);
    exitText.setPosition(100, 350);
    exitText.setFillColor(sf::Color::White);
}

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

void updateHUD(float angle, float power) {
    shotsText.setString("Disparos: " + std::to_string(shotCount));
    angleText.setString("Ángulo: " + std::to_string(static_cast<int>(angle * 180 / 3.14159f)));
    powerText.setString("Potencia: " + std::to_string(static_cast<int>(power)));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TP - Ragdoll Cannon");
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    initializeMenu();
    initializeHUD();

    // Piso y límites del mundo
    b2BodyDef groundDef;
    groundDef.position.Set(0.f, 0.f);
    b2Body* ground = world.CreateBody(&groundDef);

    b2EdgeShape edge;

    // Piso
    edge.SetTwoSided(b2Vec2(0, 6), b2Vec2(8, 6));
    ground->CreateFixture(&edge, 0.0f);

    // Lista de ragdolls
    std::list<Ragdoll> ragdolls;

    // Cañón
    sf::Vector2f cannonPos(100.f, 500.f);
    sf::Vector2f mouseWorld = cannonPos;
    float currentPower = 0.f;
    float cannonAngle = 0.f;

    sf::Vertex shotLine[2];
    shotLine[0].color = sf::Color::Red;
    shotLine[1].color = sf::Color::Red;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (state == MENU) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    state = PLAYING;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }
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
            }
        }

        world.Step(1.f / 60.f, 8, 3);
        window.clear();

        if (state == MENU) {
            window.draw(title);
            window.draw(startText);
            window.draw(exitText);
        }
        else if (state == PLAYING) {
            shotLine[0].position = cannonPos;
            shotLine[1].position = cannonPos + sf::Vector2f(std::cos(cannonAngle), std::sin(cannonAngle)) * currentPower;
            window.draw(shotLine, 2, sf::Lines);

            for (auto& ragdoll : ragdolls)
                ragdoll.draw(window);

            window.draw(shotsText);
            window.draw(angleText);
            window.draw(powerText);
        }

        window.display();
    }

    return 0;
}

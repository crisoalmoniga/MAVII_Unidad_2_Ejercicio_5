#include "BoxWall.h"
#define SCALE 100.0f

// Constructor: crea una pared de cajas apiladas
BoxWall::BoxWall(b2World& world, int rows, int cols, float startX, float startY) {
    float boxWidth = 20.0f;
    float boxHeight = 80.0f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // Posición de cada caja
            float x = startX + col * boxWidth;
            float y = startY - row * boxHeight;

            // Definición del cuerpo físico
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(x / SCALE, y / SCALE);
            b2Body* boxBody = world.CreateBody(&bodyDef);

            // Forma de la caja
            b2PolygonShape boxShape;
            boxShape.SetAsBox((boxWidth / 2) / SCALE, (boxHeight / 2) / SCALE);

            // Definición del fixture
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &boxShape;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.5f;
            boxBody->CreateFixture(&fixtureDef);

            // Almacenar el cuerpo
            boxBodies.push_back(boxBody);

            // Representación visual
            auto shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(boxWidth, boxHeight));
            shape->setOrigin(boxWidth / 2, boxHeight / 2);
            shape->setFillColor(sf::Color::Blue);
            boxShapes.push_back(std::move(shape));
        }
    }
}

// Dibujar la pared de cajas
void BoxWall::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < boxBodies.size(); ++i) {
        b2Vec2 pos = boxBodies[i]->GetPosition();
        float angle = boxBodies[i]->GetAngle() * 180 / b2_pi;
        boxShapes[i]->setPosition(pos.x * SCALE, pos.y * SCALE);
        boxShapes[i]->setRotation(angle);
        window.draw(*boxShapes[i]);
    }
}

// Verificar si todas las cajas están en el suelo (nivel completado)
bool BoxWall::isCleared() const {
    for (const auto& body : boxBodies) {
        if (body->GetPosition().y * SCALE > 500) {
            return false;
        }
    }
    return true;
}

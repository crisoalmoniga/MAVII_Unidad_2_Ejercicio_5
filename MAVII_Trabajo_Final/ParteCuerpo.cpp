#include "ParteCuerpo.h"

// Factor de escala para transformar coordenadas físicas a píxeles
#define SCALE 100.0f

// Constructor por defecto: crea una parte del cuerpo con color amarillo
ParteCuerpo::ParteCuerpo(b2World& world, float x, float y, float width, float height)
    : ParteCuerpo(world, x, y, width, height, sf::Color::Yellow) {}

// Constructor con parámetros específicos (incluye color)
ParteCuerpo::ParteCuerpo(b2World& world, float x, float y, float width, float height, sf::Color color) {
    // Definición del cuerpo dinámico de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;                     // Tipo dinámico para permitir movimiento
    bodyDef.position.Set(x / SCALE, y / SCALE);         // Posición inicial escalada
    body = world.CreateBody(&bodyDef);                  // Crear el cuerpo en el mundo físico

    // Definición de la forma del cuerpo (rectángulo)
    b2PolygonShape shape;
    shape.SetAsBox((width / 4) / SCALE, (height / 4) / SCALE);  // Ajuste del tamaño, escalado

    // Configuración de la fixture (propiedades físicas)
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;                         // Asigna la forma al fixture
    fixtureDef.density = 5.0f;                         // Densidad del cuerpo
    fixtureDef.friction = 0.6f;                        // Fricción para el movimiento
    fixtureDef.restitution = 0.0f;                     // Restitución (rebote) del cuerpo
    fixtureDef.filter.categoryBits = 0x0001;           // Categoría de colisión
    fixtureDef.filter.maskBits = 0xFFFF;               // Máscara de colisión (colisiona con todo)
    body->CreateFixture(&fixtureDef);                  // Crear el fixture en el cuerpo

    // Configuración del rectángulo para SFML (visualización)
    rect.setSize(sf::Vector2f(width, height));          // Dimensiones del rectángulo
    rect.setOrigin(width / 2, height / 2);              // Origen en el centro para rotación
    rect.setFillColor(color);                          // Color del rectángulo
}

// Método para dibujar el cuerpo en la ventana SFML
void ParteCuerpo::draw(sf::RenderWindow& window) {
    // Obtener la posición y rotación del cuerpo físico
    b2Vec2 pos = body->GetPosition();                   // Posición en coordenadas físicas
    float angle = body->GetAngle() * 180 / b2_pi;       // Convertir el ángulo de radianes a grados

    // Actualizar la posición y la rotación del rectángulo visual
    rect.setPosition(pos.x * SCALE, pos.y * SCALE);     // Transformación de coordenadas físicas a píxeles
    rect.setRotation(angle);                           // Asignación de la rotación
    window.draw(rect);                                 // Dibuja el rectángulo en la ventana
}

// Método para obtener el puntero al cuerpo físico de Box2D
b2Body* ParteCuerpo::getBody() {
    return body;                                       // Devuelve el cuerpo físico asociado
}

// Método para obtener la posición actual del cuerpo en coordenadas SFML
sf::Vector2f ParteCuerpo::getPosition() const {
    b2Vec2 pos = body->GetPosition();                   // Obtener la posición del cuerpo en Box2D
    return sf::Vector2f(pos.x * SCALE, pos.y * SCALE);  // Convertir a coordenadas de pantalla
}
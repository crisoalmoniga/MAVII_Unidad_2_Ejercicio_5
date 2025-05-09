#include "ParteCuerpo.h"

// Factor de escala para transformar coordenadas f�sicas a p�xeles
#define SCALE 100.0f

// Constructor por defecto: crea una parte del cuerpo con color amarillo
ParteCuerpo::ParteCuerpo(b2World& world, float x, float y, float width, float height)
    : ParteCuerpo(world, x, y, width, height, sf::Color::Yellow) {}

// Constructor con par�metros espec�ficos (incluye color)
ParteCuerpo::ParteCuerpo(b2World& world, float x, float y, float width, float height, sf::Color color) {
    // Definici�n del cuerpo din�mico de Box2D
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;                     // Tipo din�mico para permitir movimiento
    bodyDef.position.Set(x / SCALE, y / SCALE);         // Posici�n inicial escalada
    body = world.CreateBody(&bodyDef);                  // Crear el cuerpo en el mundo f�sico

    // Definici�n de la forma del cuerpo (rect�ngulo)
    b2PolygonShape shape;
    shape.SetAsBox((width / 4) / SCALE, (height / 4) / SCALE);  // Ajuste del tama�o, escalado

    // Configuraci�n de la fixture (propiedades f�sicas)
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;                         // Asigna la forma al fixture
    fixtureDef.density = 5.0f;                         // Densidad del cuerpo
    fixtureDef.friction = 0.6f;                        // Fricci�n para el movimiento
    fixtureDef.restitution = 0.0f;                     // Restituci�n (rebote) del cuerpo
    fixtureDef.filter.categoryBits = 0x0001;           // Categor�a de colisi�n
    fixtureDef.filter.maskBits = 0xFFFF;               // M�scara de colisi�n (colisiona con todo)
    body->CreateFixture(&fixtureDef);                  // Crear el fixture en el cuerpo

    // Configuraci�n del rect�ngulo para SFML (visualizaci�n)
    rect.setSize(sf::Vector2f(width, height));          // Dimensiones del rect�ngulo
    rect.setOrigin(width / 2, height / 2);              // Origen en el centro para rotaci�n
    rect.setFillColor(color);                          // Color del rect�ngulo
}

// M�todo para dibujar el cuerpo en la ventana SFML
void ParteCuerpo::draw(sf::RenderWindow& window) {
    // Obtener la posici�n y rotaci�n del cuerpo f�sico
    b2Vec2 pos = body->GetPosition();                   // Posici�n en coordenadas f�sicas
    float angle = body->GetAngle() * 180 / b2_pi;       // Convertir el �ngulo de radianes a grados

    // Actualizar la posici�n y la rotaci�n del rect�ngulo visual
    rect.setPosition(pos.x * SCALE, pos.y * SCALE);     // Transformaci�n de coordenadas f�sicas a p�xeles
    rect.setRotation(angle);                           // Asignaci�n de la rotaci�n
    window.draw(rect);                                 // Dibuja el rect�ngulo en la ventana
}

// M�todo para obtener el puntero al cuerpo f�sico de Box2D
b2Body* ParteCuerpo::getBody() {
    return body;                                       // Devuelve el cuerpo f�sico asociado
}

// M�todo para obtener la posici�n actual del cuerpo en coordenadas SFML
sf::Vector2f ParteCuerpo::getPosition() const {
    b2Vec2 pos = body->GetPosition();                   // Obtener la posici�n del cuerpo en Box2D
    return sf::Vector2f(pos.x * SCALE, pos.y * SCALE);  // Convertir a coordenadas de pantalla
}
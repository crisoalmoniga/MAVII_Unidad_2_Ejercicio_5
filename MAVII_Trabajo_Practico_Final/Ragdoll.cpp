#include "Ragdoll.h"
#include <cmath>

Ragdoll::Ragdoll(b2World& world, sf::Vector2f position, float angle, float potencia) {
    // Cuerpo principal del ragdoll
    cabeza = std::make_unique<ParteCuerpo>(world, position.x, position.y - 20, 10, 10);
    torso = std::make_unique<ParteCuerpo>(world, position.x, position.y, 16.5f, 16.5f);
    brazoIzq = std::make_unique<ParteCuerpo>(world, position.x - 11, position.y, 10, 3.5f);
    brazoDer = std::make_unique<ParteCuerpo>(world, position.x + 11, position.y, 10, 3.5f);
    piernaIzq = std::make_unique<ParteCuerpo>(world, position.x - 3.5f, position.y + 20, 4, 15);
    piernaDer = std::make_unique<ParteCuerpo>(world, position.x + 3.5f, position.y + 20, 4, 15);

    // Crear juntas para conectar partes del cuerpo
    b2Vec2 centroTorso = torso->getBody()->GetWorldCenter();
    auto unir = [&](b2Body* a, b2Body* b, b2Vec2 puntoMundo) {
        b2RevoluteJointDef jointDef;
        jointDef.bodyA = a;
        jointDef.bodyB = b;
        jointDef.localAnchorA = a->GetLocalPoint(puntoMundo);
        jointDef.localAnchorB = b->GetLocalPoint(puntoMundo);
        jointDef.collideConnected = false;
        world.CreateJoint(&jointDef);
        };

    unir(cabeza->getBody(), torso->getBody(), centroTorso + b2Vec2(0, -0.1f));
    unir(brazoIzq->getBody(), torso->getBody(), centroTorso + b2Vec2(-0.1f, 0));
    unir(brazoDer->getBody(), torso->getBody(), centroTorso + b2Vec2(0.1f, 0));
    unir(piernaIzq->getBody(), torso->getBody(), centroTorso + b2Vec2(-0.035f, 0.125f));
    unir(piernaDer->getBody(), torso->getBody(), centroTorso + b2Vec2(0.035f, 0.125f));
}

void Ragdoll::update() {
    // Actualiza la posición del ragdoll si es necesario
    cabeza->update();
    torso->update();
    brazoIzq->update();
    brazoDer->update();
    piernaIzq->update();
    piernaDer->update();
}


void Ragdoll::draw(sf::RenderWindow& window) {
    cabeza->draw(window);
    torso->draw(window);
    brazoIzq->draw(window);
    brazoDer->draw(window);
    piernaIzq->draw(window);
    piernaDer->draw(window);
}
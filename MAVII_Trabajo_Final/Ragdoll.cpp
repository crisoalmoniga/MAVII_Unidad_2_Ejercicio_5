#include "Ragdoll.h"
#include <cmath>

// Factor de escala para convertir entre coordenadas f�sicas y p�xeles
#define SCALE 100.0f

// Constructor de la clase Ragdoll
Ragdoll::Ragdoll(b2World& world, sf::Vector2f origen, float anguloCanon, float potencia) {

    // Crear las partes del cuerpo del ragdoll usando smart pointers (std::unique_ptr)

    // Cabeza del ragdoll (c�rculo)
    cabeza = std::make_unique<ParteCuerpo>(world, origen.x, origen.y - 20, 10, 10);

    // Torso del ragdoll (cuadrado)
    torso = std::make_unique<ParteCuerpo>(world, origen.x, origen.y, 16.5f, 16.5f);

    // Brazos izquierdo y derecho (rect�ngulos)
    brazoIzq = std::make_unique<ParteCuerpo>(world, origen.x - 11, origen.y, 10, 3.5f);
    brazoDer = std::make_unique<ParteCuerpo>(world, origen.x + 11, origen.y, 10, 3.5f);

    // Piernas izquierda y derecha (rect�ngulos largos)
    piernaIzq = std::make_unique<ParteCuerpo>(world, origen.x - 3.5f, origen.y + 20, 4, 15);
    piernaDer = std::make_unique<ParteCuerpo>(world, origen.x + 3.5f, origen.y + 20, 4, 15);

    // Obtener el centro del torso para usar como punto de referencia
    b2Vec2 centroTorso = torso->getBody()->GetWorldCenter();

    // Funci�n lambda para unir dos partes del cuerpo usando un joint (articulaci�n)
    auto unir = [&](b2Body* a, b2Body* b, b2Vec2 puntoMundo, bool limitado = false) {
        b2RevoluteJointDef jointDef;            // Definici�n de un joint revoluto (articulaci�n con rotaci�n)
        jointDef.bodyA = a;                     // Primer cuerpo a unir
        jointDef.bodyB = b;                     // Segundo cuerpo a unir
        jointDef.localAnchorA = a->GetLocalPoint(puntoMundo); // Punto de anclaje en el primer cuerpo
        jointDef.localAnchorB = b->GetLocalPoint(puntoMundo); // Punto de anclaje en el segundo cuerpo
        jointDef.collideConnected = false;      // Evitar colisiones entre los cuerpos conectados

        // Configuraci�n de l�mites de rotaci�n si est� habilitado
        jointDef.enableLimit = limitado;
        if (limitado) {
            jointDef.lowerAngle = -0.5f;        // L�mite inferior del �ngulo
            jointDef.upperAngle = 0.5f;         // L�mite superior del �ngulo
        }

        // Crear el joint en el mundo f�sico
        world.CreateJoint(&jointDef);
        };

    // Conectar las partes del ragdoll usando los joints

    // Unir la cabeza al torso
    unir(cabeza->getBody(), torso->getBody(), centroTorso + b2Vec2(0, -0.1f));

    // Unir los brazos al torso (con l�mite de rotaci�n)
    unir(brazoIzq->getBody(), torso->getBody(), centroTorso + b2Vec2(-0.1f, 0), true);
    unir(brazoDer->getBody(), torso->getBody(), centroTorso + b2Vec2(0.1f, 0), true);

    // Unir las piernas al torso (sin l�mite de rotaci�n)
    unir(piernaIzq->getBody(), torso->getBody(), centroTorso + b2Vec2(-0.035f, 0.125f));
    unir(piernaDer->getBody(), torso->getBody(), centroTorso + b2Vec2(0.035f, 0.125f));

    // Calcular el impulso inicial para lanzar el ragdoll
    float impulseFactor = potencia * 0.0055f;    // Factor de escala para la fuerza de impulso
    b2Vec2 impulso = impulseFactor * b2Vec2(std::cos(anguloCanon), std::sin(anguloCanon));

    // Aplicar el impulso al centro del torso para que el ragdoll salga disparado
    torso->getBody()->ApplyLinearImpulseToCenter(impulso, true);
}

// M�todo para dibujar el ragdoll en la pantalla
void Ragdoll::draw(sf::RenderWindow& window) {
    // Dibujar todas las partes del ragdoll
    cabeza->draw(window);
    torso->draw(window);
    brazoIzq->draw(window);
    brazoDer->draw(window);
    piernaIzq->draw(window);
    piernaDer->draw(window);
}
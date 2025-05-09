#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>


// Constructor de la clase Game
Game::Game(int ancho, int alto, std::string titulo)
{
    // Inicializaci�n de la ventana y configuraci�n de propiedades
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setVisible(true);
    fps = 60;
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom(); // Configuraci�n de la vista del juego
    InitPhysics(); // Inicializaci�n del motor de f�sica

    // Crear una caja en la posici�n inicial
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(50.0f, 50.0f);
    controlBody = phyWorld->CreateBody(&boxDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(5.0f, 5.0f); // Tama�o de la caja

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 90.0f; // Densidad
    boxFixtureDef.friction = 50.0f; // Coeficiente de rozamiento
    boxFixtureDef.restitution = 0.0f; // Coeficiente de restituci�n

    controlBody->CreateFixture(&boxFixtureDef);
}

// Destructor de la clase
Game::~Game(void)
{ }

// Bucle principal del juego
void Game::Loop()
{
    while (wnd->isOpen())
    {
        wnd->clear(clearColor); // Limpiar la ventana
        DoEvents(); // Procesar eventos de entrada
        UpdatePhysics(); // Actualizar la simulaci�n f�sica
        DrawGame(); // Dibujar el juego
        wnd->display(); // Mostrar la ventana
    }
}

// Actualizaci�n de la simulaci�n f�sica
void Game::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8); // Simular el mundo f�sico
    phyWorld->ClearForces(); // Limpiar las fuerzas aplicadas a los cuerpos
    phyWorld->DebugDraw(); // Dibujar el mundo f�sico para depuraci�n

    // Aplicar fuerza a la caja seg�n las teclas izquierda/derecha
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        controlBody->ApplyForceToCenter(b2Vec2(-0.9f, 0.0f), true);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        controlBody->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
    }
}

// Dibujo de los elementos del juego
void Game::DrawGame()
{

}

// Procesamiento de eventos de entrada
void Game::DoEvents()
{
    Event evt;
    while (wnd->pollEvent(evt))
    {
        switch (evt.type)
        {
        case Event::Closed:
            wnd->close(); // Cerrar la ventana si se presiona el bot�n de cerrar
            break;
        }
    }

    // Controlar el movimiento del cuerpo de control con el teclado
    // Segun la numeracion usada, cuando mas cerca de cero mas 
    // lento es el desplazamiento sobre ese eje
    controlBody->SetAwake(true);
    if (Keyboard::isKeyPressed(Keyboard::Left))
        controlBody->SetLinearVelocity(b2Vec2(-9.0f, 0.0f));
    if (Keyboard::isKeyPressed(Keyboard::Right))
        controlBody->SetLinearVelocity(b2Vec2(9.0f, 0.0f));
    if (Keyboard::isKeyPressed(Keyboard::Down))
        controlBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    if (Keyboard::isKeyPressed(Keyboard::Up))
        controlBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

// Comprobaci�n de colisiones (a implementar m�s adelante)
void Game::CheckCollitions()
{
    // Implementaci�n de la comprobaci�n de colisiones
}

// Configuraci�n de la vista del juego
void Game::SetZoom()
{
    View camara;
    // Posicionamiento y tama�o de la vista
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara); // Asignar la vista a la ventana
}

// Inicializaci�n del motor de f�sica y los cuerpos del mundo f�sico
void Game::InitPhysics()
{
    // Inicializar el mundo f�sico con la gravedad por defecto
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

    // Crear un renderer de debug para visualizar el mundo f�sico
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    // Crear el suelo inclinado (plano inclinado)
    b2BodyDef inclineBodyDef;
    inclineBodyDef.type = b2_staticBody;
    inclineBodyDef.position.Set(10.0f, 70.0f); // Posici�n del plano inclinado

    b2Body* inclineBody = phyWorld->CreateBody(&inclineBodyDef);

    b2PolygonShape inclineShape;

    // Tama�o del plano inclinado (ancho y altura)
    float width = 100.0f;
    float height = 100.0f; // Ajusta la altura seg�n el �ngulo del plano
    inclineShape.SetAsBox(width / 2.0f, height / 2.0f);

    b2FixtureDef inclineFixtureDef;
    inclineFixtureDef.shape = &inclineShape;

    inclineBody->CreateFixture(&inclineFixtureDef);

    // Cambia el �ngulo del plano inclinado (en radianes)
    float inclineAngle = 45.0f; // Por ejemplo, 45 grados
    b2Vec2 position(10.0f, 70.0f); // Posici�n del plano inclinado
    inclineBody->SetTransform(position, b2_pi * inclineAngle / 180.0f); // Configura la posici�n y la rotaci�n del cuerpo

    // Crear la caja
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(50.0f, 50.0f);
    controlBody = phyWorld->CreateBody(&boxDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(5.0f, 5.0f); // Tama�o de la caja

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 90.0f; // Densidad
    boxFixtureDef.friction = 50.0f; // Coeficiente de rozamiento
    boxFixtureDef.restitution = 0.0f; // Coeficiente de restituci�n

    controlBody->CreateFixture(&boxFixtureDef);
}

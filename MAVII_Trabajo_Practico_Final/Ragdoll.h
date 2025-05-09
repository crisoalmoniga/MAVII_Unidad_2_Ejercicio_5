#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <memory>
#include "ParteCuerpo.h"

class Ragdoll {
public:
    Ragdoll(b2World& world, sf::Vector2f position, float angle, float potencia);
    void update();
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<ParteCuerpo> head;
    std::unique_ptr<ParteCuerpo> torso;
    std::unique_ptr<ParteCuerpo> leftArm;
    std::unique_ptr<ParteCuerpo> rightArm;
    std::unique_ptr<ParteCuerpo> leftLeg;
    std::unique_ptr<ParteCuerpo> rightLeg;
};
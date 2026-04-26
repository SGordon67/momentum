#include "PhysicalObj.h"

// INHERITED FROM VISIBLEOBJ
// int m_objectID;
// RenderLayer m_renderLayer;
// sf::Texture* m_texture;
// sf::IntRect m_spriteRect;
// sf::Sprite m_sprite;
// sf::Vector2f m_velocity = {0, 0};
// float m_acceleration = 5000;
// float m_maxVelocity = 500;
// sf::Angle m_angularVelocity = sf::degrees(0);

// float m_mass = 10;
// float m_radius = 10; // for collisions
// float m_dragCoef = 4;

PhysicalObj::PhysicalObj(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
                         float maxVelocity, float acceleration, sf::Angle angularVelocity)
: VisibleObj(position, size, rotation, renderLayer, texture, maxVelocity, acceleration, angularVelocity)
{
}

void PhysicalObj::addDragForce(sf::Vector2f &currentVelocity, float mass, float dt) {
    currentVelocity.x = currentVelocity.x * (1.f - m_dragCoef * dt / mass);
    currentVelocity.y = currentVelocity.y * (1.f - m_dragCoef * dt / mass);
}

void PhysicalObj::addAccelerationForce(sf::Vector2f &currentVelocity, float acceleration,
        sf::Angle dir, float maximumVelocity, float mass, float dt)
{
    // get the maximum components
    float maxXVelocity = maximumVelocity * std::abs(std::cos(dir.asRadians()));
    float maxYVelocity = maximumVelocity * std::abs(std::sin(dir.asRadians()));

    sf::Vector2f fAccel = {0, 0};
    if (acceleration != 0){
        fAccel.x = (-acceleration / mass) * std::cos(dir.asRadians()) * dt;
        fAccel.y = (-acceleration / mass) * std::sin(dir.asRadians()) * dt;
    }
    sf::Vector2f newVelocity = {currentVelocity.x + fAccel.x,
        currentVelocity.y + fAccel.y};

    // only add acceleration if we wouldn't go over the max
    if (std::abs(newVelocity.x) <= maxXVelocity)
        currentVelocity.x = newVelocity.x;
    if (std::abs(newVelocity.y) <= maxYVelocity)
        currentVelocity.y = newVelocity.y;
}

void PhysicalObj::updateVelocity(sf::Angle dir, float acceleration, float dt){
}
void PhysicalObj::update(float dt){
}
void PhysicalObj::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}

#include <SFML/System/Vector2.hpp>

#include "VisibleObj.h"

extern int numObjects;

// int m_objectID;
// RenderLayer m_renderLayer;
// sf::Texture* m_texture;
// sf::IntRect m_spriteRect;
// sf::Sprite m_sprite;
//
// sf::Vector2f m_velocity = {0, 0};
// float m_maxVelocity = 500;
// float m_acceleration = 5000;
// sf::Angle m_angularVelocity = 0;

VisibleObj::VisibleObj(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
                       float maxVelocity, float acceleration, sf::Angle angularVelocity)
    : m_objectID(++numObjects),
    m_renderLayer(renderLayer),
    m_texture(texture),
    m_spriteRect(sf::Vector2i(0, 0), size),
    m_sprite(*texture, m_spriteRect),
    m_maxVelocity(maxVelocity),
    m_acceleration(acceleration),
    m_angularVelocity(angularVelocity)
{
    m_sprite.setTexture(*texture);
    m_sprite.setOrigin({size.x/2.f, size.y/2.f});
    m_sprite.setPosition(position);
    m_sprite.setRotation(rotation);
}

void VisibleObj::updatePosition(float dt){
    m_sprite.move(m_velocity * dt);
}

void VisibleObj::updateVelocity(sf::Angle dir, float acceleration, float dt)
{
    // zero out the velocity if its small enough
    if(getVelocity().x < 0.5 && getVelocity().x > -0.5) setVelocity({0, getVelocity().y});
    if(getVelocity().y < 0.5 && getVelocity().y > -0.5) setVelocity({getVelocity().x, 0});

    sf::Angle direction = dir;

    // calculate the change in velocity based on acceleration/direction/maximumVelocity
    // get the maximum components based on direction
    float maxXVelocity = m_maxVelocity * std::abs(std::cos(direction.asRadians()));
    float maxYVelocity = m_maxVelocity * std::abs(std::sin(direction.asRadians()));
    sf::Vector2f accel = {0, 0};
    if (m_acceleration != 0)
    {
        accel.x = (-m_acceleration) * std::cos(direction.asRadians()) * dt;
        accel.y = (-m_acceleration) * std::sin(direction.asRadians()) * dt;
    }
    sf::Vector2f newVelocity = {getVelocity().x + accel.x,
        getVelocity().y + accel.y};

    // make sure we don't go over the directional maxVelocity
    if (std::abs(newVelocity.x) <= maxXVelocity)
        m_velocity.x = newVelocity.x;
    if (std::abs(newVelocity.y) <= maxYVelocity)
        m_velocity.y = newVelocity.y;
}
void VisibleObj::update(float dt){
    updateVelocity(getRotation(), m_acceleration, dt);
    m_sprite.move(m_velocity);
    m_sprite.rotate(m_angularVelocity);
}
void VisibleObj::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}

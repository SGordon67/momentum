#include <SFML/System/Vector2.hpp>

#include "Entity.h"

Entity::Entity(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
               float maxVelocity, float acceleration, sf::Angle angularVelocity, int maxHP,
               float mass, float radius, float drag)
    : PhysicalObj(position, size, rotation, renderLayer, texture, maxVelocity, acceleration, angularVelocity, mass, radius, drag)
    , m_hp(maxHP)
    , m_maxHP(maxHP)
    , m_markedForDeath(false)
{
}
void Entity::reduceHealth(int damage){
    // m_visualObjects->push_back(std::make_unique<DamageNum>(getPosition(), damage));
    setHP(getHP() - damage);
    if(getHP() <= 0) {
        m_hp = 0;
        markForDeath();
    }
}

void Entity::increaseHealth(int heal){
    m_hp += heal;
    if(m_hp > m_maxHP) m_hp = m_maxHP;
    std::cout << "HEALED, NEW HP -- " << getHP() << std::endl;
}

void Entity::updateVelocity(sf::Angle dir, float acceleration, float dt){
}
void Entity::update(float dt){
}
void Entity::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}

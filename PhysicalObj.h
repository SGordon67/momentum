#ifndef PHYSICALOBJ_H
#define PHYSICALOBJ_H

#include "VisibleObj.h"

class PhysicalObj : public VisibleObj{
protected:
    float m_mass = 10;
    float m_radius = 10; // for collisions
    float m_dragCoef = 4;
public:
    PhysicalObj(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
                float maxVelocity, float acceleration, sf::Angle angularVelocity);

    float getMass() { return m_mass; }
    float getRadius() { return m_radius; }
    float getDragCoef() { return m_dragCoef; }
    
    void addDragForce(sf::Vector2f &currentVelocity, float mass, float dt);
    void addAccelerationForce(sf::Vector2f &currentVelocity, float acceleration,
                              sf::Angle dir, float maximumVelocity, float mass, float dt);

    virtual void updateVelocity(sf::Angle dir, float acceleration, float dt) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
};

#endif

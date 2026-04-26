#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InputSystem.h"
#include "SFML/Graphics/Shader.hpp"

class Player : public Entity {
private:
    // default values
    static constexpr sf::Vector2f d_playerPosition = {50, 50};
    static constexpr sf::Vector2i d_playerSize = {64, 64};
    static constexpr sf::Angle d_playerAngle = sf::degrees(0.f);
    static constexpr int d_playerMass = 10;
    static constexpr float d_playerRadius = d_playerSize.x/2.f;
    static constexpr sf::Vector2f d_playerVelocity = {0, 0};
    static constexpr float d_playerAcceleration = 5000;
    static constexpr float d_playerAngularVelocity = 0;
    static constexpr float d_playerMaxVelocity = 500;
    static constexpr float d_playerDrag = 4;

    // current and max hp to play with default usually 100 each
    static constexpr int d_playerHP = 100;
    static constexpr int d_playerMaxHP = 100;

    static constexpr sf::Angle d_playerAngularAcceleration = sf::degrees(4.f);

    InputSystem* m_input;
    sf::Shader m_shader;

    sf::Glsl::Mat3 m_rotationMatrix = sf::Glsl::Mat3({1,0,0, 0,1,0, 0,0,1});

public:
    Player(InputSystem* input, sf::Texture* texture);
    Player(InputSystem* input, sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture,
           float maxVelocity, float acceleration, sf::Angle angularVelocity, int maxHP,
           float mass, float radius, float drag);

    float determineAcceleration(InputSystem* input);
    sf::Angle determineDirection(InputSystem* input);

    void updateRotation(float dt);
    virtual void updateVelocity(sf::Angle dir, float acceleration, float dt) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
};

#endif

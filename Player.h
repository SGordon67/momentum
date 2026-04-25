#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

// Entity(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP)
class Player : public Entity {
private:
    // default values
    static constexpr sf::Vector2f d_playerPosition = {900, 500};
    static constexpr sf::Vector2i d_playerSize = {0, 0};
    static constexpr sf::Angle d_playerAngle = sf::degrees(90.f);
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

    static constexpr float d_playerAngularAcceleration = (4.f * (M_PI / 180.f));
public:
    Player(sf::Texture* texture);
    Player(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP);

    virtual void update();
    virtual void render(sf::RenderWindow& window);
};

#endif

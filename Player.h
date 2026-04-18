#ifndef PLAYER_H
#define PLAYER_H

#include "PhysicalObj.h"

class Player : public PhysicalObj {
private:
public:
    Player(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture);

    virtual void update();
    virtual void render(sf::RenderWindow& window);
};

#endif

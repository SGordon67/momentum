#ifndef PHYSICALOBJ_H
#define PHYSICALOBJ_H

#include "VisibleObj.h"

class PhysicalObj : public VisibleObj{
protected:
public:
    PhysicalObj(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture);

    virtual void update();
    virtual void render(sf::RenderWindow& window);
};

#endif

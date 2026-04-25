#ifndef ENTITY_H
#define ENTITY_H

#include "PhysicalObj.h"
#include "VisibleObj.h"
#include <iostream>

class Entity : public PhysicalObj {
protected:
	int m_hp;
	int m_maxHP;
    bool m_markedForDeath;
    std::vector<VisibleObj> visuals;
public:
    Entity(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP);

	int getHP() const { return m_hp; }
    void setHP(int hp){ m_hp = hp; }

	int getMaxHP() const { return m_maxHP; }
    void setMaxHP(int hp){ m_maxHP = hp; }
    void markForDeath(){ m_markedForDeath = true; }
    bool isMarkedForDeath(){ return m_markedForDeath; }

	void reduceHealth(int damage);
	void increaseHealth(int heal);

    virtual void update();
    virtual void render(sf::RenderWindow& window);
};

#endif

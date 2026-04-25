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
    Entity(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP)
        : PhysicalObj(position, size, rotation, renderLayer, texture)
        , m_hp(maxHP)
        , m_maxHP(maxHP)
        , m_markedForDeath(false){
    }

	int getHP() const {
		return m_hp;
	}
    void setHP(int hp){
        m_hp = hp;
    }

	int getMaxHP() const {
		return m_maxHP;
	}
    void setMaxHP(int hp){
        m_maxHP = hp;
    }
    void markForDeath(){
        m_markedForDeath = true;
    }
    bool isMarkedForDeath(){
        return m_markedForDeath;
    }

	void reduceHealth(int damage){
        // m_visualObjects->push_back(std::make_unique<DamageNum>(getPosition(), damage));

        setHP(getHP() - damage);
        if(getHP() <= 0) {
            m_hp = 0;
            markForDeath();
        }
	}

	void increaseHealth(int heal){
		m_hp += heal;
		if(m_hp > m_maxHP) m_hp = m_maxHP;
        std::cout << "HEALED, NEW HP -- " << getHP() << std::endl;
	}
};

#endif

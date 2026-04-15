#ifndef VISIBLEOBJ_H
#define VISIBLEOBJ_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Angle.hpp>
#include <cmath>

#include "enums.h"

class VisibleObj {
protected:
    int m_objectID;
    RenderLayer m_renderLayer;
    sf::Texture* m_texture;
    sf::IntRect m_spriteRect;
    sf::Sprite m_sprite;
public:
    VisibleObj(sf::Vector2f position, sf::Vector2i size, float rotation, RenderLayer renderLayer, sf::Texture* texture);

    int getObjectID() const { return m_objectID; }
    RenderLayer getRenderLayer() const { return m_renderLayer; }
    sf::Texture* getTexture() { return m_texture; }
    sf::IntRect getRect() { return m_spriteRect; }
    sf::Sprite getSprite() { return m_sprite; }

    sf::Vector2f getPosition() { return m_sprite.getPosition(); }
    sf::Vector2f getScale() { return m_sprite.getScale(); }
    sf::Angle getRotation() { return m_sprite.getRotation(); }

    void setPosition(sf::Vector2f position) { m_sprite.setPosition(position); }
    void setRenderLayer(RenderLayer layer) { m_renderLayer = layer; }
    void setRotation(sf::Angle rotation) { m_sprite.setRotation(rotation); }
    void rotate(const sf::Angle rotation) {
        m_sprite.rotate(rotation);
        if(m_sprite.getRotation() >= sf::degrees(360)) m_sprite.setRotation(m_sprite.getRotation() - sf::degrees(360));
        if(m_sprite.getRotation() < sf::degrees(0)) m_sprite.setRotation(m_sprite.getRotation() + sf::degrees(360));
    }
    virtual void update();
	virtual void render(sf::RenderWindow& window);
};

#endif

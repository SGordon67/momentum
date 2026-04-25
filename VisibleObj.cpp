#include <SFML/System/Vector2.hpp>

#include "VisibleObj.h"

extern int numObjects;

VisibleObj::VisibleObj(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture)
    : m_objectID(++numObjects)
    , m_renderLayer(renderLayer)
    , m_texture(texture)
    , m_spriteRect(sf::Vector2i(0, 0), size)
    , m_sprite(*texture, m_spriteRect)
{
    m_sprite.setTexture(*texture);
    m_sprite.setOrigin({size.x/2.f, size.y/2.f});
    m_sprite.setPosition(position);
    m_sprite.setRotation(rotation);
}
void VisibleObj::update(){
}
void VisibleObj::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}

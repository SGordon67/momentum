#include "PhysicalObj.h"

// INHERITED FROM VISIBLEOBJ
// int m_objectID;
// RenderLayer m_renderLayer;
// sf::Texture* m_texture;
// sf::IntRect m_spriteRect;
// sf::Sprite m_sprite;

PhysicalObj::PhysicalObj(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture)
    : VisibleObj(position, size, rotation, renderLayer, texture)
{
}
void PhysicalObj::update(){
}
void PhysicalObj::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}

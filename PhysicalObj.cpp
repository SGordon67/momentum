#include "PhysicalObj.h"

// int m_objectID;
// RenderLayer m_renderLayer;
// sf::Texture* m_texture;
// sf::IntRect m_spriteRect;
// sf::Sprite m_sprite;

PhysicalObj::PhysicalObj(sf::Vector2f position, sf::Vector2i size, float rotation, RenderLayer renderLayer, sf::Texture* texture)
    : VisibleObj(position, size, rotation, renderLayer, texture)
{
}
void PhysicalObj::update(){
}
void PhysicalObj::render(sf::RenderWindow& window){
}

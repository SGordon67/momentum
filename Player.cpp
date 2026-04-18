#include "Player.h"

Player::Player(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture)
    : PhysicalObj(position, size, rotation, renderLayer, texture)
{
}
void Player::update(){
}
void Player::render([[maybe_unused]] sf::RenderWindow& window){
}

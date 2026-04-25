#include "Player.h"

Player::Player(sf::Texture* texture)
: Entity(d_playerPosition, d_playerSize, d_playerAngle, RenderLayer::Main, texture, d_playerMaxHP){
}
Player::Player(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP)
: Entity(position, size, rotation, renderLayer, texture, maxHP){
}
void Player::update(){
}
void Player::render(sf::RenderWindow& window){
    window.draw(m_sprite);
}

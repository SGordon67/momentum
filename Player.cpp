#include "Player.h"

// Entity(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP)
Player::Player(sf::Texture* texture)
: Entity(d_playerPosition, d_playerSize, sf::Angle::asDegrees(90), RenderLayer::Main, texture, d_playerMaxHP){
}
Player::Player(sf::Vector2f position, sf::Vector2i size, sf::Angle rotation, RenderLayer renderLayer, sf::Texture* texture, int maxHP)
: Entity(position, size, rotation, renderLayer, texture, maxHP){
}
void Player::update(){
}
void Player::render([[maybe_unused]] sf::RenderWindow& window){
}

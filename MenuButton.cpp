#include "MenuButton.h"
#include "SFML/Graphics/Font.hpp"

MenuButton::MenuButton(sf::Font font)
: m_text(sf::Text(font)){
    m_text.setString("Meteorite");
    m_text.setFillColor(sf::Color::White);

    m_buttonBox.setFillColor(sf::Color(50, 50, 150));
    m_buttonBox.setOutlineThickness(3);
    m_buttonBox.setOutlineColor(sf::Color::White);
}
void MenuButton::update(sf::Vector2i mousePos){
    handleHover(mousePos);
}
void MenuButton::handleHover(sf::Vector2i mousePos){
}
void MenuButton::updateLayout(sf::Vector2u windowSize){
}
void MenuButton::render(sf::RenderWindow &window){
}

#include "MenuLabel.h"

MenuLabel::MenuLabel(sf::Font font)
: m_text(sf::Text(font)){
    m_text.setString("Meteorite");
    m_text.setFillColor(sf::Color::White);
}

void MenuLabel::setString(std::string str){
    m_text.setString(str);
}
void MenuLabel::setFillColor(sf::Color color){
    m_text.setFillColor(color);
}

void updateLayout(sf::Vector2u windowSize){
}
void render(sf::RenderWindow &window){
}

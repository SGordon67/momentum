#include "MenuLabel.h"

MenuLabel::MenuLabel(const sf::Font& font, std::string str, sf::Color txColor, float txSize)
: m_text(sf::Text(font)), m_txColor(txColor), m_txSizeFraction(txSize){
    m_text.setString(str);
    m_text.setFillColor(m_txColor);
    m_text.setOutlineColor(m_txColor);
    m_text.setOutlineThickness(1);
}
sf::Text MenuLabel::getText(){
    return m_text;
}
void MenuLabel::setString(std::string str){
    m_text.setString(str);
}
void MenuLabel::setFillColor(sf::Color color){
    m_text.setFillColor(color);
}
void MenuLabel::setOutlineThickness(int thicc){
    m_text.setOutlineThickness(thicc);
}
void MenuLabel::updateLayout(sf::Vector2u windowSize, float xFrac, float yFrac){
    m_text.setCharacterSize(windowSize.y * m_txSizeFraction);

    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x , textBounds.position.y});
    m_text.setPosition({windowSize.x * xFrac, (windowSize.y * yFrac)});
}
void MenuLabel::render(sf::RenderWindow &window){
    window.draw(m_text);
}

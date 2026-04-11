#include "MenuLabel.h"

MenuLabel::MenuLabel(const sf::Font& font, std::string str, sf::Color txColor, float txSize)
: m_text(sf::Text(font)), m_txColor(txColor), m_txSizeFraction(txSize){
    m_text.setString(str);
    m_text.setFillColor(sf::Color::White);
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
void MenuLabel::updateLayout(sf::Vector2u windowSize){
    m_text.setCharacterSize(windowSize.y * m_txSizeFraction);
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f});
    m_text.setPosition({windowSize.x / 2.f, windowSize.y / 3.f});
}
void MenuLabel::render(sf::RenderWindow &window){
    window.draw(m_text);
}

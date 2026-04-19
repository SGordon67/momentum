#include "MenuButton.h"
#include "SFML/Graphics/Font.hpp"

extern void centerTextInBox(sf::Text& text, const sf::RectangleShape& box, float xMargin, float yMargin);

MenuButton::MenuButton(const sf::Font& font, std::string str, sf::Vector2f buttonSizeFraction, float marginX, float marginY,
                       sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor)
    : m_text(sf::Text(font)), m_buttonSizeFraction(buttonSizeFraction), m_marginX(marginX), m_marginY(marginY),
    m_bgColor(bgColor), m_hvbgColor(hvbgColor), m_txColor(txColor), m_hvtxColor(hvtxColor), m_olColor(olColor){

    m_text.setString(str);
    m_text.setFillColor(m_txColor);
    m_text.setOutlineColor(m_txColor);
    m_text.setOutlineThickness(0);

    m_buttonBox.setFillColor(m_bgColor);
    m_buttonBox.setOutlineThickness(3);
    m_buttonBox.setOutlineColor(m_olColor);

    // default size/position, to be changed with updateLayout
    m_text.setCharacterSize(10);
    m_text.setPosition({10,10});
    m_buttonBox.setSize({10, 10});
    m_buttonBox.setPosition({10, 10});
}
sf::Text MenuButton::getText(){
    return m_text;
}
sf::RectangleShape MenuButton::getButton(){
    return m_buttonBox;
}
void MenuButton::hover(){
    m_text.setFillColor(m_hvtxColor);
    m_buttonBox.setFillColor(m_hvbgColor);
}
void MenuButton::unhover(){
    m_text.setFillColor(m_txColor);
    m_buttonBox.setFillColor(m_bgColor);
}
bool MenuButton::isHovered(sf::Vector2i mousePos) const {
    return m_buttonBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
void MenuButton::updateLayout(sf::Vector2u windowSize, float buttonXposFraction, float buttonYposFraction){
    sf::Vector2f size = {
        windowSize.x * m_buttonSizeFraction.x,
        windowSize.y * m_buttonSizeFraction.y
    };

    sf::Vector2f pos = {
        windowSize.x * buttonXposFraction,
        windowSize.y * buttonYposFraction
    };

    m_buttonBox.setSize(size);
    m_buttonBox.setPosition(pos);

    centerTextInBox(m_text, m_buttonBox, m_marginX, m_marginY);
}
void MenuButton::render(sf::RenderWindow &window){
    window.draw(m_buttonBox);
    window.draw(m_text);
}

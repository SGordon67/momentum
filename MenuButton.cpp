#include "MenuButton.h"
#include "MainMenu.h"
#include "SFML/Graphics/Font.hpp"

MenuButton::MenuButton(const sf::Font& font, std::string str, sf::Vector2f buttonSizeFraction, float marginX, float marginY,
                       sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor)
    : m_text(sf::Text(font)), m_buttonSizeFraction(buttonSizeFraction), m_marginX(marginX), m_marginY(marginY),
    m_bgColor(bgColor), m_hvbgColor(hvbgColor), m_txColor(txColor), m_hvtxColor(hvtxColor), m_olColor(olColor){

    m_text.setString(str);
    m_text.setFillColor(m_txColor);
    m_text.setOutlineColor(m_txColor);
    m_text.setOutlineThickness(1);

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
void MenuButton::select(){
    m_text.setFillColor(m_hvtxColor);
    m_buttonBox.setFillColor(m_hvbgColor);
}
void MenuButton::unselect(){
    m_text.setFillColor(m_txColor);
    m_buttonBox.setFillColor(m_bgColor);
}
bool MenuButton::isHovered(sf::Vector2i mousePos) const {
    return m_buttonBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
void MenuButton::updateLayout(sf::Vector2u windowSize, float buttonXposFraction, float buttonYposFraction){
    // sizes
    m_buttonBox.setSize({(windowSize.x * m_buttonSizeFraction.x), (windowSize.y * m_buttonSizeFraction.y)});
    sf::FloatRect buttonBounds = m_buttonBox.getLocalBounds();
    m_text.setCharacterSize(buttonBounds.size.y * m_marginY);

    // positions
    m_buttonBox.setPosition({(windowSize.x * buttonXposFraction), 
        (windowSize.y * buttonYposFraction)});
    sf::FloatRect textBounds = m_text.getLocalBounds();
    m_text.setOrigin({textBounds.position.x , textBounds.position.y + (textBounds.size.y / 2.f)});
    m_text.setPosition({(windowSize.x * buttonXposFraction) + (m_buttonBox.getSize().x * m_buttonXMargin),
        ((windowSize.y * buttonYposFraction) + (m_buttonBox.getSize().y / 2.f))});
}
void MenuButton::render(sf::RenderWindow &window){
    window.draw(m_buttonBox);
    window.draw(m_text);
}

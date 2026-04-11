#include "MenuButton.h"
#include "MainMenu.h"
#include "SFML/Graphics/Font.hpp"

MenuButton::MenuButton(const sf::Font& font, std::string str, sf::Vector2f buttonSizeFraction, float marginY,
                       sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor)
    : m_text(sf::Text(font)), m_buttonSizeFraction(buttonSizeFraction), m_marginY(marginY),
    m_bgColor(bgColor), m_hvbgColor(hvbgColor), m_txColor(txColor), m_hvtxColor(hvtxColor), m_olColor(olColor){

    m_text.setString(str);
    m_text.setFillColor(m_txColor);

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
bool MenuButton::isHovered(sf::Vector2i mousePos) const
{
    return m_buttonBox.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
void MenuButton::handleHover(sf::Vector2i mousePos){
    if(isHovered(mousePos)){
        m_text.setFillColor(m_hvtxColor);
        m_buttonBox.setFillColor(m_hvbgColor);
    }else{
        m_text.setFillColor(m_txColor);
        m_buttonBox.setFillColor(m_bgColor);
    }
}
void MenuButton::update(sf::Vector2i mousePos){
    handleHover(mousePos);
}
void MenuButton::updateLayout(sf::Vector2u windowSize, float buttonXposFraction, float buttonYposFraction){
    // sizes
    m_buttonBox.setSize({(windowSize.x * m_buttonSizeFraction.x), (windowSize.y * m_buttonSizeFraction.y)});
    sf::FloatRect buttonBounds = m_buttonBox.getLocalBounds();

    float charSize = buttonBounds.size.y * (1.f - (m_marginY * 2.f));
    if (charSize < 1.f) charSize = 1.f;
    m_text.setCharacterSize(static_cast<unsigned int>(charSize));

    // positions
    m_buttonBox.setPosition({(windowSize.x * buttonXposFraction) - (m_buttonBox.getSize().x / 2.f), 
        (windowSize.y * buttonYposFraction)});
    m_text.setPosition({(windowSize.x / 2.f) - (m_text.getLocalBounds().size.x / 2.f), 
        (buttonBounds.position.y - (m_buttonBox.getSize().y * m_marginY))});
}
void MenuButton::render(sf::RenderWindow &window){
    window.draw(m_buttonBox);
    window.draw(m_text);
}

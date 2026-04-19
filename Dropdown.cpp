#include "Dropdown.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Glyph.hpp"

extern void centerTextInBox(sf::Text& text, const sf::RectangleShape& box, float xMargin, float yMargin);

Dropdown::Dropdown(const sf::Font& font, const std::vector<std::string>& options, sf::Vector2f sizeFraction, float buttonXMargin, float buttonYMargin,
                   sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor,
                   int selectedIndex)
    : m_mainText(sf::Text(font))
    , m_sizeFraction(sizeFraction)
    , m_buttonYMargin(buttonYMargin)
    , m_bgColor(bgColor), m_hvbgColor(hvbgColor), m_txColor(txColor), m_hvtxColor(hvtxColor), m_olColor(olColor)
{
    m_mainText.setString(options[0]);
    // m_mainText.setString(options[selectedIndex]);

    for(const auto& opt : options){
        sf::Text text(font);
        text.setString(opt);
        m_optionTexts.push_back(text);

        sf::RectangleShape box;
        m_optionBoxes.push_back(box);
    }
    // setSelectedIndex(selectedIndex);
}
int Dropdown::getSize(){
    return m_optionBoxes.size();
}
// 0 if closed, number of options if open
bool Dropdown::isOpen(){
    return m_isOpen;
}

std::vector<sf::RectangleShape>& Dropdown::getBoxes(){
    return m_optionBoxes;
}
int Dropdown::getSelectedIndex() const{
    return m_selectedIndex;
}
std::string Dropdown::getSelectedOption() const{
    return m_optionTexts[m_selectedIndex].getString();
}

void Dropdown::toggle(){
    m_isOpen = !m_isOpen;
}
void Dropdown::close(){
    m_isOpen = false;
}
void Dropdown::hover(int index){
    // hovering the main box
    if(index == -1){
        m_mainText.setFillColor(m_hvtxColor);
        m_mainBox.setFillColor(m_hvbgColor);
        for(size_t i = 0; i < m_optionBoxes.size(); i++){
            m_optionTexts[i].setFillColor(m_txColor);
            m_optionBoxes[i].setFillColor(m_bgColor);
        }
        return;
    }
    else{
        for(size_t i = 0; i < m_optionBoxes.size(); i++){
            m_mainText.setFillColor(m_txColor);
            m_mainBox.setFillColor(m_bgColor);
            if(static_cast<int>(i) == index){
                m_optionTexts[i].setFillColor(m_hvtxColor);
                m_optionBoxes[i].setFillColor(m_hvbgColor);
            }
            else{
                m_optionTexts[i].setFillColor(m_txColor);
                m_optionBoxes[i].setFillColor(m_bgColor);
            }
        }
    }
}
void Dropdown::unhover(){
    m_mainText.setFillColor(m_txColor);
    m_mainBox.setFillColor(m_bgColor);
    for(size_t i = 0; i < m_optionBoxes.size(); i++){
        m_optionTexts[i].setFillColor(m_txColor);
        m_optionBoxes[i].setFillColor(m_bgColor);
    }
}
bool Dropdown::isHovered(sf::Vector2i mousePos) const{
    if(m_mainBox.getGlobalBounds().contains((sf::Vector2f)mousePos)){
        return true;
    }
    return false;
}
void Dropdown::select(int index){
    if(index >= 0 && index < static_cast<int>(m_optionBoxes.size())){
        m_selectedIndex = index;
        m_mainText.setString(m_optionTexts[index].getString());
    }
}
void Dropdown::setSelectedIndex(int index){
    if(index >= 0 && index < static_cast<int>(m_optionBoxes.size())){
        m_selectedIndex = index;
        m_mainText.setString(m_optionTexts[index].getString());
    }
}

void Dropdown::handleClick(sf::Vector2i mousePos){
    if(isHovered(mousePos)){
        m_isOpen = !m_isOpen;
        return;
    }

    if(m_isOpen){
        for(size_t i = 0; i < m_optionBoxes.size(); i++){
            if(m_optionBoxes[i].getGlobalBounds().contains((sf::Vector2f)mousePos)){
                m_selectedIndex = i;
                m_mainText.setString(m_optionTexts[i].getString());
                m_isOpen = false;
                return;
            }
        }
        m_isOpen = false;
    }
}
void Dropdown::updateLayout(sf::Vector2u windowSize, float xFrac, float yFrac){
    sf::Vector2f size = { windowSize.x * m_sizeFraction.x, windowSize.y * m_sizeFraction.y};
    sf::Vector2f pos = { windowSize.x * xFrac, windowSize.y * yFrac};

    // mainbox
    m_mainBox.setSize(size);
    m_mainBox.setPosition(pos);
    centerTextInBox(m_mainText, m_mainBox, m_buttonXMargin, m_buttonYMargin);

    // options
    for(size_t i = 0; i < m_optionBoxes.size(); i++){
        sf::Vector2f optPos = pos + sf::Vector2f(0, size.y * (i + 1));
        m_optionBoxes[i].setSize(size);
        m_optionBoxes[i].setPosition(optPos);
        centerTextInBox(m_optionTexts[i], m_optionBoxes[i], m_buttonXMargin, m_buttonYMargin);
    }
}

void Dropdown::render(sf::RenderWindow& window){
    window.draw(m_mainBox);
    window.draw(m_mainText);

    if(m_isOpen){
        for(size_t i = 0; i < m_optionBoxes.size(); i++){
            window.draw(m_optionBoxes[i]);
            window.draw(m_optionTexts[i]);
        }
    }
}

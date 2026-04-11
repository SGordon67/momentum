#include <iostream>

#include "MainMenu.h"

// static const float m_titleYSizeFraction = 0.2f;
// static const float m_titleYPosFraction = 0.3f;
// static const float m_titleXPosFraction = 0.5f;
//
// static const float m_buttonYposFraction = 0.5f;
// static const float m_buttonXposFraction = 0.5f;
// static const float m_buttonYposMargin = 0.05f; // space between buttons vertically
// static const float m_buttonYMargin = 0.02; // space between text and border of button
// static const float m_buttonWidth = 0.35f;
// static const float m_buttonHeight = 0.04f;
//
// static const sf::Color m_titleTextColor = sf::Color::Green;
// static const sf::Color m_buttonTextColor = sf::Color::Green;
// static const sf::Color m_buttonHvTextColor = sf::Color::White;
// static const sf::Color m_buttonBgColor = sf::Color::White;
// static const sf::Color m_buttonHvBgColor = sf::Color::Green;
// static const sf::Color m_buttonOlColor = sf::Color::Green;

// MenuButton(sf::Font font, std::string str, float marginX, float marginY, 
//            sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor);

MainMenu::MainMenu(const sf::Font& font)
: m_title(font, "Momentum", m_titleTextColor, m_titleYSizeFraction), m_MenuButtons(){
    std::cout << "In constructor for main menu" << std::endl;
    m_MenuButtons.push_back(MenuButton(font, "Play", {m_buttonWidth, m_buttonHeight}, m_buttonYMargin,
                                       m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor));
    m_MenuButtons.push_back(MenuButton(font, "Settings", {m_buttonWidth, m_buttonHeight}, m_buttonYMargin,
                                       m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor));
    std::cout << "Created the two buttons in the constructor" << std::endl;
}
int MainMenu::select(sf::Vector2i mousePos){
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        if(m_MenuButtons[i].isHovered(mousePos)) return i;
    }
    return -1; // -1 if no button is hovered
}
void MainMenu::update(sf::Vector2i mousePos){
    std::cout << "Updating Buttons" << std::endl;
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        m_MenuButtons[i].update(mousePos);
    }
}
void MainMenu::updateLayout(sf::Vector2u windowSize){
    m_title.updateLayout(windowSize);
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        m_MenuButtons[i].updateLayout(windowSize, m_buttonXposFraction, m_buttonYposFraction + (i * (m_buttonYposMargin + m_buttonHeight)));
    }
}
void MainMenu::render(sf::RenderWindow &window){
    m_title.render(window);
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        m_MenuButtons[i].render(window);
    }
}

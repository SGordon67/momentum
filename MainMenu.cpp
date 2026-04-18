#include <iostream>

#include "MainMenu.h"
#include "InputSystem.h"

MainMenu::MainMenu(const sf::Font& font)
: m_title(font, "Momentum", m_titleTextColor, m_titleYSizeFraction), m_MenuButtons(), m_selection(0){
    m_title.setOutlineThickness(3);
    m_MenuButtons.push_back(MenuButton(font, "Play", {m_buttonWidth, m_buttonHeight}, m_buttonXMargin, m_buttonYMargin,
                                       m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor));
    m_MenuButtons.push_back(MenuButton(font, "Options", {m_buttonWidth, m_buttonHeight}, m_buttonXMargin, m_buttonYMargin,
                                       m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor));
    m_MenuButtons.push_back(MenuButton(font, "Exit", {m_buttonWidth, m_buttonHeight}, m_buttonXMargin, m_buttonYMargin,
                                       m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor));
}
int MainMenu::getSelection(){
    return m_selection;
}
void MainMenu::incSelection(){
    m_selection++;
    if(m_selection >= static_cast<int>(m_MenuButtons.size())) m_selection = 0;
}
void MainMenu::decSelection(){
    m_selection--;
    if(m_selection < 0) m_selection = m_MenuButtons.size()-1;
}
int MainMenu::handleClick(sf::Vector2i mousePos){
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        if(m_MenuButtons[i].isHovered(mousePos)) return i;
    }
    return -1; // -1 if no button is hovered
}
void MainMenu::update(sf::Vector2i mousePos, InputSystem& inputSystem){
    // update the option selection
    if(inputSystem.isNewlyPressed(Button::Up)){
        decSelection();
    }else if(inputSystem.isNewlyPressed(Button::Down) || inputSystem.isNewlyPressed(Button::Tab)){
        incSelection();
    }
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        if(m_MenuButtons[i].isHovered(mousePos)){
            m_selection = i;
        }
    }

    // update the selected button/deselect others
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        if(static_cast<int>(i) == m_selection){
            m_MenuButtons[i].hover();
        } else m_MenuButtons[i].unhover();
    }
}

void MainMenu::updateLayout(sf::Vector2u windowSize){
    m_title.updateLayout(windowSize, m_titlePosFraction.x, m_titlePosFraction.y);
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        m_MenuButtons[i].updateLayout(windowSize, m_buttonXposFraction, m_buttonYposFraction + (i * (m_buttonYposMargin + m_buttonHeight)));
    }
}
void MainMenu::render(sf::RenderWindow &window){
    m_title.render(window);
    for(size_t i = 0; i < m_MenuButtons.size(); i++){
        if(m_selection == static_cast<int>(i)) m_MenuButtons[i].hover();
        m_MenuButtons[i].render(window);
    }
}

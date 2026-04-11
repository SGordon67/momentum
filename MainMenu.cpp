#include "MainMenu.h"

MainMenu::MainMenu(sf::Font font, sf::Vector2u windowSize)
: m_title(font){
}
void MainMenu::update(sf::Vector2i mousePos){
    for(int i = 0; i < m_MenuButtons.size(); i++){
        m_MenuButtons[i].update(mousePos);
    }
}
void MainMenu::handleHover(sf::Vector2i mousePos){
}
void MainMenu::updateLayout(sf::Vector2u windowSize){
}
void MainMenu::render(sf::RenderWindow &window){
}

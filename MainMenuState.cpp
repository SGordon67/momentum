#include <iostream>

#include "MainMenuState.h"
#include "GameState.h"
#include "MainMenu.h"

MainMenuState::MainMenuState(Context& context)
    : GameState(context),
    m_mainMenu(*context.font)
{
    m_mainMenu.updateLayout(context.window->getSize());
}
void MainMenuState::makeSelection(){
    int res = m_mainMenu.getSelection();
    makeSelection(res);
}
void MainMenuState::makeSelection(int selection){
    std::cout << "Selection made on the main menu: " << selection << std::endl;

    auto& window = *context.window;
    if(selection == 2){
        window.close();
    }
}

void MainMenuState::handleEvent(const sf::Event& event){
    auto& window = *context.window;
    if(const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()){
        if (mouseButton->button == sf::Mouse::Button::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int res = m_mainMenu.click(mousePos);
            makeSelection(res);
        }
    }
    if(context.input->isPressed(Button::Escape)){
        window.close();
    }
    if(context.input->isPressed(Button::Interact)){
        makeSelection();
    }
    if (event.is<sf::Event::Closed>()){
        window.close();
    }
}

void MainMenuState::update(float dt){
    m_mainMenu.updateLayout(context.window->getSize());
    m_mainMenu.update(sf::Mouse::getPosition(*context.window), *context.input);
}

void MainMenuState::render(sf::RenderWindow& window){
    m_mainMenu.render(window);
}

#include <iostream>

#include "GameState.h"
#include "MainMenuState.h"
#include "MainMenu.h"
#include "PlayingState.h"
#include "SettingsState.h"

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
    // std::cout << "Selection made on the main menu: " << selection << std::endl;

    auto& window = *context.window;

    if(selection == 0){
        // play button
        m_nextState = std::make_unique<PlayingState>(context);
    }
    if(selection == 1){
        // settings button
        m_nextState = std::make_unique<SettingsState>(context);
    }
    else if(selection == 2){
        // exit button
        window.close();
    }
}

void MainMenuState::handleEvent(const sf::Event& event){
    auto& window = *context.window;
    if(const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()){
        if (mouseButton->button == sf::Mouse::Button::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int res = m_mainMenu.handleClick(mousePos);
            makeSelection(res);
        }
    }
    if (event.is<sf::Event::Closed>()){
        window.close();
    }
}

std::unique_ptr<GameState> MainMenuState::update([[maybe_unused]] float dt){
    // correct the resolution if needed.
    context.window->setPosition({10, 10});
    sf::View uiView(
        {context.window->getSize().x / 2.f, context.window->getSize().y / 2.f},
        {static_cast<float>(context.window->getSize().x), static_cast<float>(context.window->getSize().y)}
    );
    context.window->setView(uiView);
    m_mainMenu.updateLayout(context.window->getSize());

    // update the menu
    m_mainMenu.update(sf::Mouse::getPosition(*context.window), *context.input);

    // gather and process the current inputs
    if(context.input->isNewlyPressed(Button::Escape)){
        context.window->close();
    }
    if(context.input->isNewlyPressed(Button::Interact)){
        makeSelection();
    }

    // change states if needed
    if(m_nextState){
        return std::move(m_nextState);
    }
    return nullptr;
}

void MainMenuState::render(sf::RenderWindow& window){
    window.clear();
    m_mainMenu.render(window);
}

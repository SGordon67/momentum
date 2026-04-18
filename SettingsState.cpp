#include "SettingsState.h"
#include "MainMenuState.h"
#include <iostream>

SettingsState::SettingsState(Context& context)
    : GameState(context)
    , m_settingsMenu(*context.font)
{
}
void SettingsState::makeSelection(){
    int res = m_settingsMenu.getSelection();
    makeSelection(res);
}
void SettingsState::makeSelection(int selection){
    std::cout << "Selection made on the settings menu: " << selection << std::endl;

    if(selection == 0){
        // resolution button
        std::cout << "Selected Resolution" << std::endl;
    }
    if(selection == 1){
        // back button
        std::cout << "Selected Back" << std::endl;
    }
}

void SettingsState::handleEvent(const sf::Event& event){
    auto& window = *context.window;

    if(const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()){
        if (mouseButton->button == sf::Mouse::Button::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            m_settingsMenu.handleClick(mousePos);
        }
    }
    if (event.is<sf::Event::Closed>()){
        window.close();
    }
}

std::unique_ptr<GameState> SettingsState::update(float dt){
    m_settingsMenu.updateLayout(context.window->getSize());
    m_settingsMenu.update(sf::Mouse::getPosition(*context.window), *context.input);

    if(m_settingsMenu.shouldGoBack()){
        return std::make_unique<MainMenuState>(context);
    }
    static int lastResolution = -1;
    int current = m_settingsMenu.getResolutionIndex();

    if(current != lastResolution){
        lastResolution = current;

        std::cout << "Resolution changed to index: " << current << std::endl;

        // TODO: resize the window
    }

    return nullptr;
}

void SettingsState::render(sf::RenderWindow& window){
    window.clear();
    m_settingsMenu.render(window);
}

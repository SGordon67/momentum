#include "SettingsState.h"
#include "MainMenuState.h"
#include "SFML/System/Vector2.hpp"
#include <iostream>

SettingsState::SettingsState(Context& context)
    : GameState(context)
    , m_settingsMenu(*context.font, context.resolutionIndex, context.testIndex)
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
        std::cout << "Selected Test" << std::endl;
    }
    if(selection == 2){
        // back button
        std::cout << "Selected Back" << std::endl;
    }
}
sf::Vector2u SettingsState::getResolutionFromIndex(int index) {
    switch(index) {
        case 0: return {1920, 1080};
        case 1: return {1440, 900};
        case 2: return {1024, 900};
        case 3: return {900, 900};
        default: return {1440, 900};
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

std::unique_ptr<GameState> SettingsState::update([[maybe_unused]] float dt){
    m_settingsMenu.updateLayout(context.window->getSize());
    m_settingsMenu.update(sf::Mouse::getPosition(*context.window), *context.input);

    if(m_settingsMenu.shouldGoBack()){
        return std::make_unique<MainMenuState>(context);
    }
    if(context.input->isNewlyPressed(Button::Escape)){
        if(m_settingsMenu.inDropdown()){
            int selectedDD = m_settingsMenu.getActiveDropdownIndex();
            m_settingsMenu.closeDropdown(selectedDD);
            m_settingsMenu.setSelection(selectedDD);
        }
        else{
            return std::make_unique<MainMenuState>(context);
        }
    }
    if(context.input->isNewlyPressed(Button::Interact)){
        m_settingsMenu.handleInteract();
    }

    // update settings in context
    context.testIndex = m_settingsMenu.getTestIndex();

    // update the resolution, create new window if needed
    int current = m_settingsMenu.getResolutionIndex();
    if(current != m_lastResolution){
        m_lastResolution = current;
        context.resolutionIndex = current;
        sf::Vector2u newSize = getResolutionFromIndex(current);
        auto& window = *context.window;

        window.create(
            sf::VideoMode({newSize.x, newSize.y}),
            "momentum",
            sf::Style::Titlebar | sf::Style::Close
        );
        window.setPosition({10, 10});
        window.setVerticalSyncEnabled(true);

        sf::View uiView(
            {newSize.x / 2.f, newSize.y / 2.f},
            {static_cast<float>(newSize.x), static_cast<float>(newSize.y)}
        );
        window.setView(uiView);
        m_settingsMenu.updateLayout(window.getSize());
    }
    return nullptr;
}

void SettingsState::render(sf::RenderWindow& window){
    window.clear();
    m_settingsMenu.render(window);
}

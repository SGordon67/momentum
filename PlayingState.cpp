#include <iostream>

#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"

PlayingState::PlayingState(Context& context)
    : GameState(context)
{
}
void PlayingState::handleEvent(const sf::Event& event){
    auto& window = *context.window;
    if(const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()){
        if (mouseButton->button == sf::Mouse::Button::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "In game click at (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
        }
    }
    if (event.is<sf::Event::Closed>()){
        window.close();
    }
}

std::unique_ptr<GameState> PlayingState::update(float dt){
    if(context.input->isNewlyPressed(Button::Escape)){
        return std::make_unique<MainMenuState>(context);
    }

    if(m_nextState){
        return std::move(m_nextState);
    }

    return nullptr;
}

void PlayingState::render(sf::RenderWindow& window){
    window.clear(sf::Color::Black);
}


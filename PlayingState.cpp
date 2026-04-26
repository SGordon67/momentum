#include <iostream>

#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"

sf::Texture loadPlayerTexture() {
    sf::Texture texture;
    if (!texture.loadFromFile("art/playerSprite1.png")) {
        std::cout << "Sprite not loaded :(" << std::endl;
    }
    return texture;
}

void PlayingState::updateViewViewport(){
    auto windowSize = context.window->getSize();

    float windowRatio = static_cast<float>(windowSize.x) / windowSize.y;
    float viewRatio = (float)m_playViewSize.x / m_playViewSize.y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    bool horizontalSpacing = windowRatio > viewRatio;

    if(horizontalSpacing){
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    } else{
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }
    m_playingView.setViewport({{posX, posY}, {sizeX, sizeY}});
}

PlayingState::PlayingState(Context& context)
    : GameState(context),
    m_playerTexture(loadPlayerTexture()),
    m_player(context.input, &m_playerTexture)
{
    m_playingView.setSize(m_basePlayingViewSize);
    m_playingView.setCenter({m_basePlayingViewSize.x / 2.f, m_basePlayingViewSize.y / 2.f});

    updateViewViewport();
}
void PlayingState::handleEvent(const sf::Event& event){
    auto& window = *context.window;
    if(const auto *mouseButton = event.getIf<sf::Event::MouseButtonPressed>()){
        if (mouseButton->button == sf::Mouse::Button::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "In game click at (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
        }
    }
    if(event.is<sf::Event::Resized>()){
        updateViewViewport();
    }
    if(event.is<sf::Event::Closed>()){
        window.close();
    }
}

std::unique_ptr<GameState> PlayingState::update([[maybe_unused]] float dt){
    auto& window = *context.window;
    window.setView(m_playingView);
    // will have to update components here once I have UI in place
    // probably will make an 'InGameUI' class or something like that

    m_player.update(dt);

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
    m_player.render(window);
}


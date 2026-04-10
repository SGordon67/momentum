#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include "enums.h"

// GLOBALS
const float FixedDeltaTime = 1.0f / 60.0f;
sf::Vector2i windowPos{1930, 10};
sf::Vector2u windowSize{1440, 900};

GameState gameState = GameState::MainMenu;

int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(
                {windowSize.x, windowSize.y}), "momentum");
            // sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setPosition(windowPos);

    // default view for UI components
    sf::View uiView({windowSize.x / 2.f, windowSize.y / 2.f},
            {static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    uiView.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    window.setView(uiView);

    // time
    sf::Clock clock;
    float timeAccumulator = 0.0f;

    while (window.isOpen())
    {
        float frameTime = clock.restart().asSeconds();
        if (frameTime > 0.25)
            frameTime = 0.25;
        timeAccumulator += frameTime;

        // event handling
        while (const std::optional event = window.pollEvent())
        {
            if (const auto *mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    switch(gameState)
                    {
                        case GameState::MainMenu:
                            break;
                        case GameState::Settings:
                            break;
                        case GameState::Playing:
                            break;
                        case GameState::Paused:
                            break;
                        case GameState::GameOver:
                            break;
                    }
                }
            }
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // update the game
        switch(gameState)
        {
            case GameState::MainMenu:
                break;
            case GameState::Settings:
                break;
            case GameState::Playing:
                break;
            case GameState::Paused:
                break;
            case GameState::GameOver:
                break;
        }

        // rendering
        switch(gameState)
        {
            case GameState::MainMenu:
                break;
            case GameState::Settings:
                break;
            case GameState::Playing:
                break;
            case GameState::Paused:
                break;
            case GameState::GameOver:
                break;
        }
        window.display();
    }
    return 0;
}

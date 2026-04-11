#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "enums.h"
#include "MainMenu.h"

// GLOBALS
// functional
const float FixedDeltaTime = 1.0f / 60.0f;

// styles
sf::Font testFont;

// window
sf::Vector2i windowPos{10, 10};
sf::Vector2u windowSize{1440, 900};

// world
sf::Vector2i worldSize{4096, 4096};

// playerView
sf::Vector2f viewSize{static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)};

GameState gameState = GameState::MainMenu;

void initializeTextures()
{
    if (!testFont.openFromFile("Fonts/Nasa21-l23X.ttf")) {
        std::cout << "Font not loaded :(" << std::endl;
    }
}
int main()
{
    initializeTextures();

    std::cout << "Initialized the textures" << std::endl;

    // window
    sf::RenderWindow window(sf::VideoMode(
                {windowSize.x, windowSize.y}), "momentum",
            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setPosition(windowPos);

    // default view for UI components
    sf::View uiView({windowSize.x / 2.f, windowSize.y / 2.f},
            {static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    uiView.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    window.setView(uiView);

    std::cout << "Setup view, about to create Main Menu" << std::endl;

    MainMenu mainMenu(testFont);
    mainMenu.updateLayout(windowSize);

    std::cout << "Create Main Menu" << std::endl;

    // time
    sf::Clock clock;
    float timeAccumulator = 0.0f;

    std::cout << "About to enter main loop" << std::endl;

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
                            {
                                int res = mainMenu.select(mousePos);
                                std::cout << "Selection made on the main menu: " << res << std::endl;
                                break;
                            }
                        case GameState::Settings:
                            {
                                break;
                            }
                        case GameState::Playing:
                            {
                                break;
                            }
                        case GameState::Paused:
                            {
                                break;
                            }
                        case GameState::GameOver:
                            {
                                break;
                            }
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
                mainMenu.update(sf::Mouse::getPosition(window));
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
                mainMenu.render(window);
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

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "MainMenuState.h"
#include "InputSystem.h"

// GLOBALS
// functional
const float FixedDeltaTime = 1.0f / 60.0f;

// styles
sf::Font testFont;

// window and views
sf::Vector2i windowPos{10, 10};
sf::Vector2u windowSize{1440, 900};
sf::Vector2u gameViewSize{500, 500};

// world
sf::Vector2i worldSize{4096, 4096};

// game
int numObjects = 0;

// playerView
sf::Vector2f viewSize{static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)};

void initializeTextures(){
    // if (!testFont.openFromFile("Fonts/Tanklager-Kompakt.ttf")){
    if (!testFont.openFromFile("Fonts/Tanklager-Original.ttf")){
        std::cout << "Font not loaded :(" << std::endl;
    }
}

void centerTextInBox(sf::Text& text, const sf::RectangleShape& box, float xMargin, float yMargin){
    sf::FloatRect boxBounds = box.getLocalBounds();
    text.setCharacterSize(boxBounds.size.y * yMargin);

    // int index = std::min(3, static_cast<int>(text.getString().getSize() - 1));
    int index = 0;
    sf::Vector2f charPos = text.findCharacterPos(index);
    char character = text.getString()[index];
    bool isBold = text.getStyle();
    sf::Glyph glyph = text.getFont().getGlyph(character, text.getCharacterSize(), isBold);

    sf::FloatRect charBounds;
    charBounds.position = { charPos.x + glyph.bounds.position.x, charPos.y + glyph.bounds.position.y };
    charBounds.size = glyph.bounds.size;

    sf::FloatRect textBounds = text.getLocalBounds();

    text.setOrigin({ textBounds.position.x, textBounds.position.y + (charBounds.size.y / 2.f)});
    text.setPosition({ box.getPosition().x + (box.getSize().x * xMargin),
        box.getPosition().y + (boxBounds.size.y * ((1.1f - yMargin) / 2.f)) + (charBounds.size.y / 2.f)});
    // the 1.1 is to custom offset to look better visually, played with that num a bit
}

int main(){
    initializeTextures();
    InputSystem inputSystem = InputSystem();

    // window
    sf::RenderWindow window(sf::VideoMode(
        {windowSize.x, windowSize.y}), "momentum",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setPosition(windowPos);

    // game states
    Context context;
    context.window = &window;
    context.font = &testFont;
    context.input = &inputSystem;
    std::unique_ptr<GameState> gameState = std::make_unique<MainMenuState>(context);

    // default view for UI components
    sf::View uiView({windowSize.x / 2.f, windowSize.y / 2.f},
                    {static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
    uiView.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    window.setView(uiView);

    sf::View gameplayView({gameViewSize.x / 2.f, gameViewSize.y / 2.f},
                          {static_cast<float>(gameViewSize.x), static_cast<float>(gameViewSize.y)});
    gameplayView.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));

    // time
    sf::Clock clock;
    float timeAccumulator = 0.0f;

    while (window.isOpen()){
        float frameTime = clock.restart().asSeconds();
        if (frameTime > 0.25)
            frameTime = 0.25;
        timeAccumulator += frameTime;

        inputSystem.updateButtonPresses();

        while (const std::optional<sf::Event> event = window.pollEvent()) {
            gameState->handleEvent(*event);
        }

        // update the game
        // also potential state transition
        auto newState = gameState->update(FixedDeltaTime);
        if(newState){
            gameState = std::move(newState);
        }

        gameState->render(window);

        window.display();
    }
    return 0;
}

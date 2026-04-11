#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

#include "MenuLabel.h"
#include "MenuButton.h"

static const float titleYSizeDivisor = 5.f;
static const float titleYPosDivisor = 3.f;
static const float titleXPosDivisor = 2.f;

static const float buttonFirstPosY = 0.5f;
static const float buttonMargin = 0.01f;

class MainMenu{
private:
    MenuLabel m_title;
    std::vector<MenuButton> m_MenuButtons;

public:
    MainMenu(sf::Font font, sf::Vector2u windowSize);
    void update(sf::Vector2i mousePos);
    void handleHover(sf::Vector2i mousePos);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

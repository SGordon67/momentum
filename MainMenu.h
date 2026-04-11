#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

#include "MenuLabel.h"
#include "MenuButton.h"

// all values are fractions of the window size to properly scale
static const float m_titleYSizeFraction = 0.2f;
static const float m_titleYPosFraction = 0.3f;
static const float m_titleXPosFraction = 0.5f;

static const float m_buttonYposFraction = 0.5f;
static const float m_buttonXposFraction = 0.5f;
static const float m_buttonYposMargin = 0.01f; // space between buttons vertically
static const float m_buttonYMargin = 0.02; // space between text and border of button
static const float m_buttonWidth = 0.35f;
static const float m_buttonHeight = 0.05f;

static const sf::Color m_titleTextColor = sf::Color::Green;
static const sf::Color m_buttonTextColor = sf::Color::Green;
static const sf::Color m_buttonHvTextColor = sf::Color::White;
static const sf::Color m_buttonBgColor = sf::Color::White;
static const sf::Color m_buttonHvBgColor = sf::Color::Green;
static const sf::Color m_buttonOlColor = sf::Color::Green;

class MainMenu{
private:
    MenuLabel m_title;
    std::vector<MenuButton> m_MenuButtons;

public:
    MainMenu(const sf::Font& font);
    void update(sf::Vector2i mousePos);
    int select(sf::Vector2i mousePos);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

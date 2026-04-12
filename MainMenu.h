#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

#include "InputSystem.h"
#include "MenuLabel.h"
#include "MenuButton.h"

// all values are fractions of the window size to properly scale
static const float m_titleYSizeFraction = 0.2f;
static const sf::Vector2f m_titlePosFraction = {0.01f, 0.02f};

static const float m_buttonYposFraction = 0.2f;
static const float m_buttonXposFraction = 0.01f;
static const float m_buttonYposMargin = 0.01f; // space between buttons vertically
static const float m_buttonYMargin = 0.90; // size of text within button
static const float m_buttonXMargin = 0.01f; // horizontal gap between side of button and text within
static const float m_buttonWidth = 0.25f;
static const float m_buttonHeight = 0.05f;

static const sf::Color m_titleTextColor = sf::Color(0x1B6629ff);
static const sf::Color m_buttonTextColor = sf::Color(0x1B6629ff);
static const sf::Color m_buttonHvTextColor = sf::Color(0x657569ff);
static const sf::Color m_buttonBgColor = sf::Color(0x657569ff);
static const sf::Color m_buttonHvBgColor = sf::Color(0x1B6629ff);
static const sf::Color m_buttonOlColor = sf::Color(0x1B6629ff);

class MainMenu{
private:
    MenuLabel m_title;
    std::vector<MenuButton> m_MenuButtons;
    int m_selection;

public:
    MainMenu(const sf::Font& font);
    int getSelection();
    void incSelection();
    void decSelection();
    int click(sf::Vector2i mousePos);
    void update(sf::Vector2i mousePos, InputSystem& inputSystem);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

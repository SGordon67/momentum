#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

#include "InputSystem.h"
#include "MenuLabel.h"
#include "MenuButton.h"

class MainMenu{
private:
    // all values are fractions of the window size to properly scale
    constexpr static const float m_titleYSizeFraction = 0.2f;
    constexpr static const sf::Vector2f m_titlePosFraction = {0.01f, 0.02f};

    constexpr static const float m_buttonYposFraction = 0.2f;
    constexpr static const float m_buttonXposFraction = 0.01f;
    constexpr static const float m_buttonYposMargin = 0.015f; // space between buttons vertically
    constexpr static const float m_buttonYMargin = 0.75f; // size of text within button
    constexpr static const float m_buttonXMargin = 0.02f; // horizontal gap between side of button and text within
    constexpr static const float m_buttonWidth = 0.25f;
    constexpr static const float m_buttonHeight = 0.06f;

    constexpr static const sf::Color m_titleTextColor = sf::Color(0x1B6629ff);
    constexpr static const sf::Color m_buttonTextColor = sf::Color(0x1B6629ff);
    constexpr static const sf::Color m_buttonHvTextColor = sf::Color(0x657569ff);
    constexpr static const sf::Color m_buttonBgColor = sf::Color(0x657569ff);
    constexpr static const sf::Color m_buttonHvBgColor = sf::Color(0x1B6629ff);
    constexpr static const sf::Color m_buttonOlColor = sf::Color(0x1B6629ff);

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

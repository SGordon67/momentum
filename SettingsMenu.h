#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

#include "Dropdown.h"
#include "InputSystem.h"
#include "MenuLabel.h"
#include "MenuButton.h"

struct SettingItem {
    MenuLabel label;
    Dropdown dropdown;
};
class SettingsMenu{
private:
    // all values are fractions of the window size to properly scale

    // sizes
    constexpr static const float m_titleYSizeFraction = 0.2f;
    constexpr static const float m_settingWidth = 0.20f; // the button
    constexpr static const float m_settingHeight = 0.06f; // the button and label

    // positions
    constexpr static const sf::Vector2f m_titlePosFraction = {0.01f, 0.02f};

    constexpr static const float m_settingItemFirstYposFraction = 0.25f;
    constexpr static const float m_settingLabelFirstXposFraction = 0.01f;
    constexpr static const float m_settingDropdownFirstXposFraction = 0.99 - m_settingWidth;

    constexpr static const float m_settingItemYposMargin = 0.015f; // space between items vertically

    constexpr static const float m_buttonYMargin = 0.75f; // size of text within button
    constexpr static const float m_buttonXMargin = 0.02f; // horizontal gap between side of button and text within

    // constexpr static const sf::Vector2f m_backButtonPosFraction = {m_settingDropdownFirstXposFraction, 0.85f};
    constexpr static const sf::Vector2f m_backButtonPosFraction = {m_settingLabelFirstXposFraction, 0.85f};

    constexpr static const sf::Color m_titleTextColor = sf::Color(0x1B6629ff);
    constexpr static const sf::Color m_buttonTextColor = sf::Color(0x1B6629ff);
    constexpr static const sf::Color m_buttonHvTextColor = sf::Color(0x657569ff);
    constexpr static const sf::Color m_buttonBgColor = sf::Color(0x657569ff);
    constexpr static const sf::Color m_buttonHvBgColor = sf::Color(0x1B6629ff);
    constexpr static const sf::Color m_buttonOlColor = sf::Color(0x1B6629ff);

    MenuLabel m_title;
    std::vector<SettingItem> m_settingsItems;
    MenuButton m_backButton;

    int m_selection = 0;
    bool m_shouldGoBack = false;

public:
    SettingsMenu(const sf::Font& font, int resolutionIndex, int testIndex);
    bool inDropdown();
    int getDropdownSize();
    int getActiveDropdownIndex();
    int getSelection();
    void setSelection(int selection);
    void incSelection();
    void decSelection();
    void handleClick(sf::Vector2i mousePos);
    void handleInteract();
    void closeDropdown(int ddIndex);

    int getResolutionIndex() const;
    int getTestIndex() const;

    bool shouldGoBack();

    void update(sf::Vector2i mousePos, InputSystem& inputSystem);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

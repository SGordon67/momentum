#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

// static const float m_titleYSizeFraction = 0.2f;
// static const sf::Vector2f m_titlePosFraction = {0.01f, 0.02f};
//
// static const float m_buttonYposFraction = 0.2f;
// static const float m_buttonXposFraction = 0.01f;
// static const float m_buttonYposMargin = 0.01f; // space between buttons vertically
// static const float m_buttonYMargin = 0.98; // size of text within button
// static const float m_buttonXMargin = 0.01f; // horizontal gap between side of button and text within
// static const float m_buttonWidth = 0.35f;
// static const float m_buttonHeight = 0.05f;
//
// static const sf::Color m_titleTextColor = sf::Color(0x1B6629ff);
// static const sf::Color m_buttonTextColor = sf::Color(0x1B6629ff);
// static const sf::Color m_buttonHvTextColor = sf::Color(0x657569ff);
// static const sf::Color m_buttonBgColor = sf::Color(0x657569ff);
// static const sf::Color m_buttonHvBgColor = sf::Color(0x1B6629ff);
// static const sf::Color m_buttonOlColor = sf::Color(0x1B6629ff);
class MenuButton{
private:
    sf::Text m_text;
    sf::RectangleShape m_buttonBox;

    const sf::Vector2f m_buttonSizeFraction;
    float m_marginX; // space between text and box
    float m_marginY; // size of text vertically

    sf::Color m_bgColor;
    sf::Color m_hvbgColor;
    sf::Color m_txColor;
    sf::Color m_hvtxColor;
    sf::Color m_olColor;

public:
    MenuButton(const sf::Font& font, std::string str, sf::Vector2f buttonSizeFraction, float marginX, float marginY,
               sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor);
    sf::Text getText();
    sf::RectangleShape getButton();
    void select();
    void unselect();
    bool isHovered(sf::Vector2i mousePos) const;
    void updateLayout(sf::Vector2u windowSize, float buttonXposFraction, float buttonYposFraction);
    void render(sf::RenderWindow &window);
};

#endif

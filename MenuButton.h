#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

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

#ifndef MAINLABEL_H
#define MAINLABEL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

class MenuLabel{
private:
    sf::Text m_text;
    sf::Color m_txColor;

    const sf::Vector2f m_txPosFraction;
    const float m_txSizeFraction;

public:
    MenuLabel(const sf::Font& font, std::string str, sf::Color txColor, sf::Vector2f txPosFraction, float txSize);
    sf::Text getText();
    void setString(std::string str);
    void setFillColor(sf::Color color);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

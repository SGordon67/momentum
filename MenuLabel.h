#ifndef MAINLABEL_H
#define MAINLABEL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

class MenuLabel{
private:
    sf::Text m_text;
    sf::Vector2f m_position;

public:
    MenuLabel(sf::Font font);
    void setString(std::string str);
    void setFillColor(sf::Color color);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

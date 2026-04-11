#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>

class MenuButton{
private:
    sf::Text m_text;
    sf::RectangleShape m_buttonBox;

public:
    MenuButton(sf::Font font);
    void update(sf::Vector2i mousePos);
    void handleHover(sf::Vector2i mousePos);
    void updateLayout(sf::Vector2u windowSize);
    void render(sf::RenderWindow &window);
};

#endif

#ifndef DROPDOWN_H
#define DROPDOWN_H

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

struct SettingSelection {
    int setting;
    std::string value;
};
class Dropdown{
private:
    sf::RectangleShape m_mainBox;
    sf::Text m_mainText;

    std::vector<sf::RectangleShape> m_optionBoxes;
    std::vector<sf::Text> m_optionTexts;

    bool m_isOpen = false;
    int m_selectedIndex = 0;

    sf::Vector2f m_sizeFraction;

    sf::Color m_bgColor;
    sf::Color m_hvbgColor;
    sf::Color m_txColor;
    sf::Color m_hvtxColor;
    sf::Color m_olColor;

public:
    Dropdown(const sf::Font& font, const std::vector<std::string>& options, sf::Vector2f sizeFraction,
             sf::Color bgColor, sf::Color hvbgColor, sf::Color txColor, sf::Color hvtxColor, sf::Color olColor);
    int getSize();
    bool isOpen();
    std::vector<sf::RectangleShape>& getBoxes();
    int getSelectedIndex() const;
    std::string getSelectedOption() const;

    void toggle();
    void close();
    void hover(int index);
    void unhover();
    bool isHovered(sf::Vector2i mousePos) const;
    void select(int index);

    void handleClick(sf::Vector2i mousePos);
    void updateLayout(sf::Vector2u windowSize, float xFrac, float yFrac);
    void render(sf::RenderWindow& window);
};

#endif

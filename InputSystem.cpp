#include <SFML/Window/Keyboard.hpp>
#include <cstddef>

#include "InputSystem.h"

InputSystem::InputSystem(){
}

void InputSystem::updateButtonPresses(){
    m_beenPressed[(size_t)Button::Escape] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && m_buttons[(size_t)Button::Escape];
    m_beenPressed[(size_t)Button::Up] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && m_buttons[(size_t)Button::Up];
    m_beenPressed[(size_t)Button::Down] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && m_buttons[(size_t)Button::Down];
    m_beenPressed[(size_t)Button::Left] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) && m_buttons[(size_t)Button::Left];
    m_beenPressed[(size_t)Button::Right] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) && m_buttons[(size_t)Button::Right];
    m_beenPressed[(size_t)Button::Interact] = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) && m_buttons[(size_t)Button::Interact];
    m_beenPressed[(size_t)Button::Tab] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) && m_buttons[(size_t)Button::Tab];

    m_buttons[(size_t)Button::Escape] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_buttons[(size_t)Button::Up] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    m_buttons[(size_t)Button::Down] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    m_buttons[(size_t)Button::Left] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    m_buttons[(size_t)Button::Right] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    m_buttons[(size_t)Button::Interact] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    m_buttons[(size_t)Button::Tab] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab);
}
bool InputSystem::isPressed(Button button) const {
    return m_buttons[(size_t)button];
}
bool InputSystem::isNewlyPressed(Button button) const {
    return (m_buttons[(size_t)button] && !m_beenPressed[(size_t)button]);
}

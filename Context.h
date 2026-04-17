#ifndef CONTEXT_H
#define CONTEXT_H

#include <SFML/Graphics.hpp>
#include "InputSystem.h"

struct Context {
    sf::RenderWindow* window;
    sf::Font* font;
    InputSystem* input;
};

#endif

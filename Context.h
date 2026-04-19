#ifndef CONTEXT_H
#define CONTEXT_H

#include <SFML/Graphics.hpp>
#include "InputSystem.h"

struct Context {
    sf::RenderWindow* window;
    sf::Font* font;
    InputSystem* input;

    int resolutionIndex = 1; // 1440x900
    int testIndex = 0;
};

#endif

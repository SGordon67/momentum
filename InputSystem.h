#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <array>

#include "enums.h"

class InputSystem
{
private:
    std::array<bool, (std::size_t)Button::Count> m_buttons{false};
    std::array<bool, (std::size_t)Button::Count> m_beenPressed{false};

public:
    InputSystem();
    void updateButtonPresses();
    bool isPressed(Button button) const;
    bool isNewlyPressed(Button button) const;
};

#endif

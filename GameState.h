#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Context.h"
#include <SFML/Graphics/RenderWindow.hpp>

class GameState {
protected:
    Context context;
public:
    GameState(Context& context) : context(context) {}
    virtual ~GameState() = default;

    virtual void handleEvent(const sf::Event& event) = 0;

    virtual std::unique_ptr<GameState> update(float dt) = 0;

    virtual void render(sf::RenderWindow& window) = 0;
};

#endif

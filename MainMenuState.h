#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "MainMenu.h"

class MainMenuState : public GameState {
private:
    MainMenu m_mainMenu;
public:
    MainMenuState(Context& context);
    void makeSelection();
    void makeSelection(int selection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif

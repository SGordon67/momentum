#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "GameState.h"
#include "SettingsMenu.h"

class SettingsState : public GameState {
private:
    SettingsMenu m_settingsMenu;
public:
    SettingsState(Context& context);
    void makeSelection();
    void makeSelection(int selection);

    void handleEvent(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif

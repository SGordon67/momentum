#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "GameState.h"
#include "SettingsMenu.h"

class SettingsState : public GameState {
private:
    SettingsMenu m_settingsMenu;
    int m_lastResolution = -1;
public:
    SettingsState(Context& context);
    void makeSelection();
    void makeSelection(int selection);

    sf::Vector2u getResolutionFromIndex(int index);

    void handleEvent(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif

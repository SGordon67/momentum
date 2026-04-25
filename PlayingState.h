#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "Player.h"
#include "GameState.h"

static sf::Texture playerTexture;

class PlayingState : public GameState {
private:
    Player m_player;
    std::vector<std::unique_ptr<VisibleObj>> m_visualObjs;
    std::vector<std::shared_ptr<PhysicalObj>> m_physicalObjs;
    std::unique_ptr<GameState> m_nextState;
public:
    PlayingState(Context& context);

    void handleEvent(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif

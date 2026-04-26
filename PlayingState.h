#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "Player.h"
#include "GameState.h"

class PlayingState : public GameState {
private:
    sf::Texture m_playerTexture;
    Player m_player;

    sf::View m_playingView;
    sf::Vector2f m_basePlayingViewSize{500.f, 500.f};

    sf::Vector2u m_playViewSize{256, 256};
    sf::Vector2u m_worldSize{2048, 2048};

    std::vector<std::unique_ptr<VisibleObj>> m_visualObjs;
    std::vector<std::shared_ptr<PhysicalObj>> m_physicalObjs;
    std::unique_ptr<GameState> m_nextState;
public:
    PlayingState(Context& context);

    void updateViewViewport();

    void handleEvent(const sf::Event& event) override;
    std::unique_ptr<GameState> update(float dt) override;
    void render(sf::RenderWindow& window) override;
};

#endif

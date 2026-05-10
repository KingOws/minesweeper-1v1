#pragma once
#include "IScene.h"
#include "lobbydiscovery.h"
#include <vector>
#include <SFML/Graphics.hpp>

class LobbyBrowsingScene : public IScene {
private:
    std::unique_ptr<LobbyDiscovery> ld;
    LobbyInfo& joiningInfo;
    PlayerAction& myPlayerActions;

        sf::Text infoLabels[3];
        sf::RectangleShape buttons[1];
        sf::Text buttonTexts[1];

        void updateInfoText();


public:
    LobbyBrowsingScene(LobbyInfo&, PlayerAction&);
    ~LobbyBrowsingScene();
    virtual void draw(sf::RenderWindow &window);
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update();
    void updateNet();

    std::unique_ptr<LobbyDiscovery> getLobbyDiscovery(){return std::move(ld);};
};
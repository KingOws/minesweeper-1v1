#pragma once
#include "IScene.h"
#include "lobbydiscovery.h"
#include <vector>
#include <SFML/Graphics.hpp>

class LobbyBrowsingScene : public IScene {
private:
    std::unique_ptr<LobbyDiscovery> ld;
    LobbyInfo& joiningInfo;

    std::vector<sf::RectangleShape> boxes;
    std::vector<sf::Text> textFields;

public:
    LobbyBrowsingScene(LobbyInfo&);
    ~LobbyBrowsingScene();
    virtual void draw(sf::RenderWindow &window);
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update();
    void updateNet();

    std::unique_ptr<LobbyDiscovery> getLobbyDiscovery(){return std::move(ld);};
};
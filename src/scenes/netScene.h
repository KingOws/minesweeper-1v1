#pragma once

#include "IScene.h"

class NetScene : public IScene{
    private:
    sf::RectangleShape boxes[2];
    sf::Text textFields[2];
    NetworkingMode networkingMode;

    public:
    NetScene();
    virtual ~NetScene();
    virtual void draw(sf::RenderWindow &window);
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update() {};
    virtual NetworkingMode getNetworkingMode(){return networkingMode;};
};

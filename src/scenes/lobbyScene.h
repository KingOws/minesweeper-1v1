#pragma once

#include "IScene.h"

class LobbyScene : public IScene{
    private:
    sf::RectangleShape boxes[2];
    sf::Font font;
    sf::Text textFields[2];
    PlayerMode playermode;

    public:
    LobbyScene();
    virtual ~LobbyScene();
    virtual void draw(sf::RenderWindow &window);
    virtual SceneAction handleEvent(sf::Vector2f &mousePos);
    virtual void update() {};
    virtual PlayerMode getPlayerMode(){return playermode;};
};

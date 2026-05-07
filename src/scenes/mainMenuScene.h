#pragma once

#include "IScene.h"
#include "lobbydiscovery.h"

class MainMenuScene : public IScene{
    private:
    sf::RectangleShape boxes[2];
    sf::Text textFields[2];
    PlayerMode playermode;

    public:
    MainMenuScene();
    MainMenuScene(sf::RenderWindow &window);
    virtual ~MainMenuScene();
    virtual void draw(sf::RenderWindow &window);
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update() {};
    virtual PlayerMode getPlayerMode(){return playermode;};
};

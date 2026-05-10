#pragma once

#include <IScene.h>
#include <SFML/Graphics.hpp>
#include "lobbydiscovery.h"

class SceneManager;

class MenuScene: public IScene{
    private:
    sf::RectangleShape boxes[3];
    sf::Text textFields[3];
    Difficulty difficulty;

    std::shared_ptr<Lobby> lobbyNet;
    
    public:
    MenuScene();
    MenuScene(std::shared_ptr<Lobby>);
    ~MenuScene();
    void init();
    virtual void draw(sf::RenderWindow &window); 
    virtual void update() {return;};
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    inline Difficulty getDiff(){return difficulty;};
};
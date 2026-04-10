#pragma once

#include "IScene.h"
#include "board.h"

class GameScene: public IScene{
    private:
    Difficulty diff;
    Board* board;

    public:
    GameScene(Difficulty d);
    ~GameScene();
    virtual void draw(sf::RenderWindow &window); 
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update();

    void checkGameWon();
    virtual SceneAction handleDevWin();
};
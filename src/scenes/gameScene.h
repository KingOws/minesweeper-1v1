#pragma once

#include "IScene.h"
#include "board.h"

class GameScene: public IScene{
    private:
    Difficulty diff;
    Board* board;
    unsigned short tileSize;
    unsigned short col;
    unsigned short row;
    sf::Vector2f offset;

    public:
    GameScene(Difficulty d, sf::RenderWindow& window);
    ~GameScene();
    virtual void draw(sf::RenderWindow &window); 
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update();

    void checkGameWon();
    virtual SceneAction handleDevWin();
};
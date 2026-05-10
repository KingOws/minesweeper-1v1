#pragma once
#include "lobby.h"
#include "gameHeader.h"


class GameScene: public IScene{
    private:
    Difficulty diff;
    Board* board;
    GameHeader* gameHeader;
    SpriteManager* sm;

    //these are horribly named
    std::shared_ptr<Lobby> net;

    sf::Clock gameClock;
    int lastSecond = 0;
    int time;
    
    unsigned short tileSize;
    unsigned short col;
    unsigned short row;
    sf::Vector2f offset;

    public:
    GameScene(Difficulty d, sf::RenderWindow& window);
    GameScene(std::shared_ptr<Lobby>);
    ~GameScene();
    virtual void draw(sf::RenderWindow &window); 
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update();

    void checkGameWon();
    virtual SceneAction handleDevWin();
};
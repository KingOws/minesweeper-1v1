#pragma once
#include "lobby.h"
#include "gameHeader.h"


class GameScene: public IScene{
    private:
    Difficulty diff;
    Board* board;
    GameHeader* gameHeader;
    SpriteManager* sm;
    int seed;

    //these are horribly named
    std::shared_ptr<Lobby> lobbyNet;

    sf::Clock gameClock;
    int lastSecond = 0;
    int time;
    
    unsigned short tileSize;
    unsigned short col;
    unsigned short row;
    inline static const sf::Vector2f offset{0.f,100.f};

    public:
    GameScene(Difficulty d, sf::RenderWindow& window);
    GameScene(std::shared_ptr<Lobby>, int, sf::RenderWindow&);
    GameScene(std::shared_ptr<Lobby>, int, sf::RenderWindow&, int);
    GameScene(std::shared_ptr<Lobby>, Difficulty, sf::RenderWindow&);
    GameScene(){}
    ~GameScene();

    void init();
    virtual void draw(sf::RenderWindow &window); 
    virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos);
    virtual SceneAction handleRightEvent(sf::Vector2f &mousePos);
    virtual void update();

    sf::Vector2f getOffset() const {return offset;};
    void checkGameWon();
    virtual SceneAction handleDevWin();
};
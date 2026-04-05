#include "gameScene.h"
#include <SFML/Graphics.hpp>

GameScene::GameScene(Difficulty d){
    int r =10, c=10, b=10;
    switch (d) {
        case Difficulty::easy:   r = 10; c = 10; b = 10; break;
        case Difficulty::medium: r = 16; c = 16; b = 40; break;
        case Difficulty::hard:   r = 16; c = 30; b = 99; break;
    }

    board = new Board(r, c, b);
    board->updateBoard(); 
}

void GameScene::draw(sf::RenderWindow &window){
    board->drawBoard(window);
}

SceneAction GameScene::handleLeftEvent(sf::Vector2f& mousePos) {
    board->revealTile(board->handleMouse(mousePos));
    return SceneAction::None;
}

SceneAction GameScene::handleRightEvent(sf::Vector2f& mousePos) {
    board->placeFlag(board->handleMouse(mousePos));
    return SceneAction::None;
}

GameScene::~GameScene(){
    delete board;
}
void GameScene::update(){}
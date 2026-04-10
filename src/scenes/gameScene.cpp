#include "gameScene.h"
#include <SFML/Graphics.hpp>

GameScene::GameScene(Difficulty d){
    int r =10, c=10, b=10;
    switch (d) {
        case Difficulty::easy:   r = 10; c = 10; b = 10; break;
        case Difficulty::medium: r = 16; c = 16; b = 40; break;
        case Difficulty::hard:   r = 16; c = 30; b = 70; break;
    }

    board = new Board(r, c, b, {100.0,100.0});
    board->updateBoard(); 
}

void GameScene::draw(sf::RenderWindow &window){
    if (board == nullptr) return;
    board->drawBoard(window);
}

SceneAction GameScene::handleLeftEvent(sf::Vector2f &mousePos) {
    if (board == nullptr) {return SceneAction::Exit;};
    // 1. If the game is already over, the next click exits to menu
    if (board->getLost() || board->getWon()) {
        if (board->getLost()) std::cout << "[Final Result] Loss" << std::endl;
        if (board->getWon()) std::cout << "[Final Result] Win!" << std::endl;
        return SceneAction::goToMainMenu; 
    }

    // 2. Standard gameplay
    if (board->revealTile(board->handleMouse(mousePos), true)) {
        board->setLost(true);
        std::cout << "BOOM!\n";
    }

    if (!board->getLost()) checkGameWon();
    return SceneAction::None;
}

SceneAction GameScene::handleDevWin(){
    board->setWon(true);
    return SceneAction::None;
}

SceneAction GameScene::handleRightEvent(sf::Vector2f &mousePos) {
    if (board == nullptr) return SceneAction::goToMenu;
    board->placeFlag(board->handleMouse(mousePos));
    return SceneAction::None;
}

GameScene::~GameScene(){
    delete board;
    board = nullptr;
}

void GameScene::update(){

}


void GameScene::checkGameWon() {
    if (board == nullptr) return;
    for(int i = 0; i < board->getCol(); i++){
        for(int j = 0; j < board->getRow(); j++){
            if(!board->getTile(i,j)->isOpened() && !board->getTile(i,j)->isBomb()){
                return;
            }
        }
    }
    board->setWon(true);
    std::cout << "Winner winner chicken dinner!";
    return;
}
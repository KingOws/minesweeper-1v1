#include "lobbybrowsingscene.h"
#include <iostream>

LobbyBrowsingScene::LobbyBrowsingScene() {
    if (!font.openFromFile("../src/fonts/arial.ttf"))
        std::cerr << "Error: could not load font" << std::endl;

    joiningInfo.hosting = false;
    ld = std::make_unique<LobbyDiscovery>(joiningInfo);
    std::cout << "joining...";
}

LobbyBrowsingScene::~LobbyBrowsingScene() {}

void LobbyBrowsingScene::update() {

}

void LobbyBrowsingScene::draw(sf::RenderWindow &window) {

}

SceneAction LobbyBrowsingScene::handleLeftEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}

SceneAction LobbyBrowsingScene::handleRightEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}
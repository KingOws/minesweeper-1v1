#include "lobbybrowsingscene.h"
#include <iostream>

LobbyBrowsingScene::LobbyBrowsingScene() {
    if (!font.openFromFile("../src/fonts/arial.ttf"))
        std::cerr << "Error: could not load font" << std::endl;

    joiningInfo.hosting = false;
    ld = std::make_unique<LobbyDiscovery>(joiningInfo);
    ld->findServer();
    std::cout << "joining...";
}

LobbyBrowsingScene::~LobbyBrowsingScene() {}


void LobbyBrowsingScene::draw(sf::RenderWindow &window) {
    for(sf::RectangleShape& rect : boxes)
        window.draw(rect);
    for(sf::Text& text : textFields){
        window.draw(text);
    }
}

SceneAction LobbyBrowsingScene::handleLeftEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}

SceneAction LobbyBrowsingScene::handleRightEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}

void LobbyBrowsingScene::update(){
    std::cout << joiningInfo.availableGames;
    if(ld){
        ld->updatePackets();
        ld->sendPackets();
        ld->receivePackets();
    }
    
    boxes.clear();
    textFields.clear();
    boxes.resize(joiningInfo.availableGames.size());
    float posx = 0, posy = 0;

    for(auto it = joiningInfo.availableGames.begin(); it != joiningInfo.availableGames.end(); it++){
        sf::RectangleShape rect;
        rect.setSize({600,100});
        rect.setFillColor({75,175,75,75});
        rect.setPosition({posx, posy});
        boxes.push_back(rect);
        posy +=100;

        std::string s = std::to_string(*it);
        sf::Text text(font, s);
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);

        // Center text inside the rect
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
            textBounds.position.y  + textBounds.size.y / 2.f});
        text.setPosition({rect.getPosition().x + rect.getSize().x / 2.f,
            rect.getPosition().y + rect.getSize().y / 2.f});
        textFields.push_back(text);
    }
}
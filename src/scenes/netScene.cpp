#include "netScene.h"
#include <iostream>

NetScene::NetScene() : textFields{sf::Text(font), sf::Text(font)} {
    if (!font.openFromFile("../src/fonts/arial.ttf")) {
        std::cerr << "Error: could not load font" << std::endl;
    }

    float posx = 100, posy = 150;
    
    for (int i = 0; i < 2; i++) {
        sf::RectangleShape& rect = boxes[i];
        sf::Text& text = textFields[i];
        rect.setSize({600,100});
        rect.setFillColor({75,175,75,75});
        rect.setPosition({posx, posy});
        posy += 150;

        switch(i) {
            case 0:
            text.setString("Host");
            break;
            case 1:
            text.setString("Join");
            break;
        }

        text.setFont(font);
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                        textBounds.position.y  + textBounds.size.y / 2.f});
        text.setPosition({rect.getPosition().x + rect.getSize().x / 2.f,
                        rect.getPosition().y + rect.getSize().y / 2.f});
    }
}


void NetScene::draw(sf::RenderWindow &window){
    for(sf::RectangleShape &rect : boxes){
        window.draw(rect);
    }
    for(sf::Text &text : textFields){
       window.draw(text);
    }
}

SceneAction NetScene::handleLeftEvent(sf::Vector2f &mousePos){
    for (int i = 0; i < 2; i++) {
        if (boxes[i].getGlobalBounds().contains(mousePos)) {
            this->networkingMode = static_cast<NetworkingMode>(i);
            if(networkingMode == NetworkingMode::hosting)
                return SceneAction::startLobby;
            if(networkingMode == NetworkingMode::joining){
                return SceneAction::searchLobby;
            }
        }
    }
    return SceneAction::None;
} 

SceneAction NetScene::handleRightEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}   

NetScene::~NetScene(){}


    
#include "menuScene.h"
#include <iostream>

MenuScene::MenuScene() : textFields{sf::Text(font), sf::Text(font), sf::Text(font)} {
    if (!font.openFromFile("../src/fonts/arial.ttf")) {
        std::cerr << "Error: could not load font" << std::endl;
    }

        float posx = 100, posy = 150;
        for (int i = 0; i < 3; i++) {
            sf::RectangleShape& rect = boxes[i];
            sf::Text& text = textFields[i];
            rect.setSize({600,100});
            rect.setFillColor({75,175,75,75});
            rect.setPosition({posx, posy});
            posy += 150;

            switch(i) {
                case 0:
                text.setString("Easy");
                break;
                case 1:
                text.setString("Medium");
                break;
                case 2:
                text.setString("Hard");
                break;
            }

            text.setFont(font);
            text.setCharacterSize(36);
            text.setFillColor(sf::Color::Black);

            // Center text inside the rect
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                        textBounds.position.y  + textBounds.size.y / 2.f});
            text.setPosition({rect.getPosition().x + rect.getSize().x / 2.f,
                        rect.getPosition().y + rect.getSize().y / 2.f});
        }
}


void MenuScene::draw(sf::RenderWindow &window){
    for(sf::RectangleShape &rect : boxes){
        window.draw(rect);
    }
    for(sf::Text &text : textFields){
       window.draw(text);
    }
}

SceneAction MenuScene::handleLeftEvent(sf::Vector2f &mousePos){
    for (int i = 0; i < 3; i++) {
        if (boxes[i].getGlobalBounds().contains(mousePos)) {
            this->difficulty = static_cast<Difficulty>(i);
            return SceneAction::startGame;
        }
    }
    return SceneAction::None;
} 

SceneAction MenuScene::handleRightEvent(sf::Vector2f &mousePos) {
    return SceneAction::None;
}

MenuScene::~MenuScene(){}


    
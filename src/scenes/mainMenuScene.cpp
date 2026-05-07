#include "mainMenuScene.h"
#include <iostream>


MainMenuScene::MainMenuScene(sf::RenderWindow &window) : textFields{sf::Text(font), sf::Text(font)} {
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
            text.setString("Multiplayer");
            break;
            case 1:
            text.setString("Single Player");
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

MainMenuScene::MainMenuScene() : textFields{sf::Text(font), sf::Text(font)} {
    if (!font.openFromFile("../fonts/arial.ttf")) {
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
            text.setString("Multiplayer");
            break;
            case 1:
            text.setString("Single Player");
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


void MainMenuScene::draw(sf::RenderWindow &window){
    for(sf::RectangleShape &rect : boxes){
        window.draw(rect);
    }
    for(sf::Text &text : textFields){
       window.draw(text);
    }

    window.setSize({800,600});
    window.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0),{800,600})));
}

SceneAction MainMenuScene::handleLeftEvent(sf::Vector2f& mousePos) {
    if (boxes[0].getGlobalBounds().contains(mousePos))
        return SceneAction::goToNetworking;
    if (boxes[1].getGlobalBounds().contains(mousePos))
        return SceneAction::goToMenu;
    return SceneAction::None;
} 

SceneAction MainMenuScene::handleRightEvent(sf::Vector2f& mousePos) {
    return SceneAction::None;
}

MainMenuScene::~MainMenuScene(){}


    
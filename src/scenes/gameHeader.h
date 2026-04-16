#pragma once
#include <SFML/Graphics.hpp>
#include "spritemanager.h"
#include <iostream>

class GameHeader{
    private:
    //Visuals
    sf::RectangleShape background;
    sf::Texture& digitTexture;
    std::vector<sf::Sprite> clockDigits;
    std::vector<sf::Sprite> mineDigits;
    sf::IntRect digitRects[10];

    //Logic
    bool loaded = 0;

    public:
    GameHeader(){
        if (!loaded) {
        if (!digitTexture.loadFromFile("../src/images/missing_image.png")) {
            std::cerr << "Failed to load missing_image.png\n";
        }
            loaded = true;
        }

        for(size_t i = 0; i < 3; i++){
            clockDigits.push_back(sf::Sprite(digitTexture));
            mineDigits.push_back(sf::Sprite(digitTexture));
        }
    }

    void updateSprite(const SpriteManager& manager, sf::Vector2f& offset, int value) {
        int index = 0;
        short hundreds = (value/100)%10;
        short tens = (value/10)%10;
        short units = = value%10;
        for()
    
    }
};
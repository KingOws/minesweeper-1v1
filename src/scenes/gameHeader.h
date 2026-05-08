#pragma once
#include <SFML/Graphics.hpp>
#include "spritemanager.h"
#include <iostream>

class GameHeader{
    private:
    //Visuals
    sf::RectangleShape background;
    sf::Texture digitTexture;
    std::vector<sf::Sprite> clockDigits;
    std::vector<sf::Sprite> mineDigits;
    sf::IntRect digitRects[10];

    //logic
    int time;
    int numFlags;
    sf::Vector2f clockOffset;
    sf::Vector2f mineOffset;

    public:
    GameHeader() : time(0), numFlags(0){
        if (!digitTexture.loadFromFile("../images/missing_image.png")) {
            std::cerr << "Failed to load missing_image.png\n";
        }

        for(size_t i = 0; i < 3; i++){
            clockDigits.push_back(sf::Sprite(digitTexture));
            mineDigits.push_back(sf::Sprite(digitTexture));
        }
    }

    GameHeader(int f, sf::Vector2f c, sf::Vector2f m) : time(0), numFlags(f), clockOffset(c), mineOffset(m){
        if (!digitTexture.loadFromFile("../images/missing_image.png")) {
            std::cerr << "Failed to load missing_image.png\n";
        }

        for(size_t i = 0; i < 3; i++){
            clockDigits.push_back(sf::Sprite(digitTexture));
            mineDigits.push_back(sf::Sprite(digitTexture));
        }
    }

    void updateSprite(const SpriteManager& manager, const int timeVal, const int flagVal) {
        int numTime[3] = {(timeVal/100)%10,(timeVal/10)%10,(timeVal/1)%10};
        int numFlags[3] = {(flagVal/100)%10,(flagVal/10)%10,(flagVal/1)%10};

        for(int i = 0; i < 3; i++){
            clockDigits.at(i).setTexture(manager.getTileSheet());
            clockDigits.at(i).setTextureRect(manager.getDigitSprite(numTime[i]));
            clockDigits.at(i).setPosition({clockOffset.x+i*26.0f,clockOffset.y});
            clockDigits.at(i).setScale({2,2});

            mineDigits.at(i).setTexture(manager.getTileSheet());
            mineDigits.at(i).setTextureRect(manager.getDigitSprite(numFlags[i]));
            mineDigits.at(i).setPosition({mineOffset.x+i*26.0f,mineOffset.y});
            mineDigits.at(i).setScale({2,2});
        }
    }

    void draw(sf::RenderWindow& window){
        window.draw(background);
        for (auto& s : clockDigits) window.draw(s);
        for (auto& s : mineDigits)  window.draw(s);
    }
};
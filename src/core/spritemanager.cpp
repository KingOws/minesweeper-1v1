#include "spritemanager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

SpriteManager::SpriteManager(int t) {
    if (!tileSheet.loadFromFile("../src/images/minesweeper_spritesheet.png")) {
        std::cerr << "Failed to load tilesheet.png\n";
    }

    if (t < 0 || t > 7) t = 0;

    theme = t;
    tileSize = 16;
    number_of_tiles = 13;
    for (int i = 0; i < number_of_tiles; i++) {
        sf::IntRect newSprite = sf::IntRect({16*theme, 16*i}, {16, 16});
        sprites.push_back(newSprite);
    }
    
}

SpriteManager::~SpriteManager() {

}

const sf::Texture& SpriteManager::getTileSheet() const {
    return tileSheet;
}

const sf::IntRect& SpriteManager::getSprite(int index) const {
    if (index < 0 || index >= sprites.size()) {
        static sf::IntRect empty;
        return empty;
    }
    return sprites[index];
}
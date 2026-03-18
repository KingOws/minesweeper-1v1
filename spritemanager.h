#pragma once
#include <SFML/Graphics.hpp>

class SpriteManager {

    private:
    sf::Texture tileSheet;
    int theme;
    int tileSize;
    int number_of_tiles;
    std::vector<sf::IntRect> sprites;

    public:
    SpriteManager(int);
    ~SpriteManager();

    const sf::Texture& getTileSheet() const;
    const sf::IntRect& getSprite(int index) const;

    // NOT OPENED
    // 8 -> 1
    // OPENED
    // FLAG
    // BOMB EXPLODED
    // BOMB REVEALED

};
#include <iostream>
#include "tile.h"
#include <SFML/Graphics.hpp>

sf::Texture Tile::defaultTexture;
bool Tile::loaded = false;

Tile::Tile() : sprite(defaultTexture) {
    this->exists = false;
    this->bomb = false;
    this->flag = false;
    this->opened = false;

    loadDefaultTexture();
}

Tile::Tile(int pos_x, int pos_y, bool isBomb) : sprite(defaultTexture) {
    this->exists = true;

    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->bomb = isBomb;
    this->flag = false;
    this->opened = false;

    // Update Board Should handle values it reads the surrounding bombs of a tile to give it a value
    this->value = -1;

    loadDefaultTexture();
    
}

Tile::~Tile() {

}

void Tile::drawTile(sf::RenderWindow& window) {
    window.draw(sprite);
}


void Tile::loadDefaultTexture() {
    if (!loaded) {
        if (!defaultTexture.loadFromFile("../src/images/missing_image.png")) {
            std::cerr << "Failed to load missing_image.png\n";
        }
        loaded = true;
    }
    sprite = sf::Sprite(defaultTexture);
}

void Tile::updateSprite(const SpriteManager& manager, sf::Vector2f& offset, bool reveal) {
    int index = 0;

    // NOT OPENED - 0
    // 8 -> 1    -- 1, 2, 3, 4, 5, 6, 7, 8
    // OPENED    -- 9
    // FLAG      -- 10
    // BOMB EXPLODED 11
    // BOMB REVEALED 12

    if (!opened) {
        if (flag) {
            index = 10; // index of flag in spritesheet
        } else {
            index = 0;  // covered tile
        }
    } else { // opened
        if (bomb) {
            if (reveal) index = 12; // revealed bomb
            if (!reveal) index = 11; // exploded bomb
        } else if (value > 0) {
            index = 9-value; // numbers 1-8
        } else {
            index = 9; // empty opened tile
        }
    }


    sprite.setTexture(manager.getTileSheet());
    sprite.setTextureRect(manager.getSprite(index)); 
    sprite.setPosition({pos_x * size+offset.x, pos_y * size+offset.y});
    sprite.setScale({size/16, size/16});
}
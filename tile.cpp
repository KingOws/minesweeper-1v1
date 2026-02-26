#include "tile.h"
#include <SFML/Graphics.hpp>

Tile::Tile() {

}

Tile::Tile(int pos_x, int pos_y, bool isBomb) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->bomb = isBomb;
    this->flag = false;

    // Update Board Should handle values it reads the surrounding bombs of a tile to give it a value
    this->value = -1;
}

Tile::~Tile() {

}

void Tile::drawTile(sf::RenderWindow& window) {
    sf::RectangleShape rect({size, size});
    rect.setPosition({getPos_x(), getPos_y()});
    rect.setFillColor(sf::Color::Blue);
}
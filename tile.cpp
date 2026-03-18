#include <iostream>
#include "tile.h"
#include <SFML/Graphics.hpp>

Tile::Tile() {
    this->exists = false;

    this->bomb = false;
    this->flag = false;
    this->opened = false;
    this->rect.setSize({0, 0});
    this->rect.setPosition({0, 0});
    this->rect.setFillColor(sf::Color::Black);
}

Tile::Tile(int pos_x, int pos_y, bool isBomb) {
    this->exists = true;

    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->bomb = isBomb;
    this->flag = false;
    this->opened = false;

    rect.setSize({size, size});
    rect.setPosition({(float) getPos_x(), (float) getPos_y()});
    rect.setFillColor(sf::Color::Blue);
    // Update Board Should handle values it reads the surrounding bombs of a tile to give it a value
    this->value = -1;
}

Tile::~Tile() {

}

void Tile::drawTile(sf::RenderWindow& window) {
    window.draw(rect);
}

void Tile::updateRect() {
    rect.setSize({size, size});
    rect.setPosition({(float) getPos_x()*size, (float) getPos_y()*size});
    if (bomb) {
        rect.setFillColor(sf::Color::Green);
        return;
    }

    if ((getPos_x()+getPos_y())%2==0) {
        rect.setFillColor(sf::Color::Blue);
    } else {
        rect.setFillColor(sf::Color::White);
    }
}
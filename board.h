#pragma once
#include "tile.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "spritemanager.h"

class Board{
    private:
        int row;
        int col;
        int numBombs;
        std::vector<Tile*> bombs;
        Tile* tiles;
        SpriteManager* sm;

    public:
        Board();
        ~Board();
        Board(int r, int c, int b);


        Tile* getTile(int x, int y) const {return &tiles[x*col+y];};
        int getSize() const {return row * col;};
        void updateBoard();
        void generateBombs();
        void placeFlag(sf::Vector2f);
        void revealTile(sf::Vector2f);
        void drawBoard(sf::RenderWindow &window);
};
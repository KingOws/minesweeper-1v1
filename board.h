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
        bool lost;
        std::vector<Tile*> bombs;
        Tile* tiles;
        SpriteManager* sm;

    public:
        Board();
        ~Board();
        Board(int r, int c, int b);


        Tile* getTile(int x, int y) const {return &tiles[y*col+x];};
        int getSize() const {return row * col;};
        bool getLost() const {return lost;};
        void setLost(bool l) {lost = l;};
        void updateBoard();
        void generateBombs();
        void showBombs();
        sf::Vector2i handleMouse(sf::Vector2f mousePos);
        void placeFlag(sf::Vector2i);
        bool revealTile(sf::Vector2i, bool clicked=true);
        void drawBoard(sf::RenderWindow &window);
        void getNeighbours(int x, int y, std::vector<Tile*>& neighbours) const;
};
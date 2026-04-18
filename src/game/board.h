#pragma once
#include "tile.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "spritemanager.h"

class Board{
    private:
        short row;
        short col;
        short numBombs;
        short numFlags;
        short counter;
        bool lost;
        bool won;
        sf::Vector2f offset;
        std::vector<Tile*> bombs;
        Tile* tiles;
        SpriteManager* sm;

    public:
        Board();
        ~Board();
        Board(int r, int c, int b, sf::Vector2f v);


        Tile* getTile(int x, int y) const {return &tiles[x*col+y];};
        int getSize() const {return row * col;};
        int getCol() const {return col;};
        int getRow() const {return row;};
        bool getLost() const {return lost;};
        void setLost(bool l) {lost = l;};
        bool getWon() const {return won;};
        int getFlag() const {return numFlags;};
        void setWon(bool w) {won = w;};
        void updateBoard();
        void generateBombs();
        void showBombs();
        sf::Vector2i handleMouse(sf::Vector2f mousePos);
        void placeFlag(sf::Vector2i);
        bool revealTile(sf::Vector2i, bool clicked=true);
        void drawBoard(sf::RenderWindow &window);
        void getNeighbours(int x, int y, std::vector<Tile*>& neighbours) const;
};
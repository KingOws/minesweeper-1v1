#pragma once
#include "tile.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <SFML/System/Vector2.hpp>

class Board{
    private:
        int row;
        int col;
        int bombs;
        Tile* tiles;

    public:
        Board();
        ~Board();
        Board(int r, int c, int b);


        inline sf::Vector2i getRandomGridPos() const {
            static std::mt19937 gen(std::random_device{}());

            std::uniform_int_distribution<> distX(0, col);
            std::uniform_int_distribution<> distY(0, row);

            return sf::Vector2i(distX(gen), distY(gen));
        };
        
        Tile* getTile(int x, int y) const {return &tiles[x*col+y];};
        void updateBoard();
        void drawBoard(sf::RenderWindow &window);
};
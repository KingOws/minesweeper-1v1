#pragma once
#include "tile.h"

class Board{
    private:
        int row;
        int col;
        Tile* tiles;

    public:
        Board();
        ~Board();
        Board(int, int);

        void drawBoard();
};
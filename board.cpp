#include "board.h"
#include <iostream>

Board::Board(){
    row = 0;
    col = 0;
    tiles = new Tile[row * col];
}

Board::Board(int r, int c){
    row = r;
    col = c;
    tiles = new Tile[row * col];
}

Board::~Board(){
    delete tiles;
}

void Board::drawBoard(){
    for(size_t i = 0; i < row; i++){
        for(size_t j = 0; j < col; j++){
            tiles[i*col+j].drawTile();
        }
    }
}
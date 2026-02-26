#include "board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

Board::Board(){
    row = 0;
    col = 0;
    tiles = new Tile[row * col];
}

Board::Board(int r, int c, int b){
    row = r;
    col = c;
    bombs = b;
    tiles = new Tile[row * col];
    for (size_t i = 0; i < bombs; i++) {

    } 
}

Board::~Board(){
    delete tiles;
}

void Board::drawBoard(sf::RenderWindow& window){
    for(size_t i = 0; i < row; i++){
        for(size_t j = 0; j < col; j++){
            getTile(i, j)->drawTile(window);
        }
    }
}

void Board::updateBoard() {
    for(size_t i = 0; i < row; i++){
        for(size_t j = 0; j < col; j++){
            Tile* currentTile = getTile(i, j);
            int bombs = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx != 0 && dy != 0) {
                        Tile* neighbour = getTile(dx, dy);
                        if (neighbour != nullptr) {
                            if (neighbour->isBomb()) {
                                bombs++;
                            }
                        }
                    }
                }
            }
            currentTile->setValue(bombs);
        }
    }
}
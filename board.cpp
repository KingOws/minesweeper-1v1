#include "board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <random>

Board::Board(){
    row = 0;
    col = 0;
    tiles = nullptr;
}

Board::Board(int r, int c, int b){
    row = r;
    col = c;
    numBombs = b;
    tiles = new Tile[row * col];
    std::cout << "Board created with: \n";
    std::cout << "ROWS: " << row << " COL: " << col << " BOMBS: " << numBombs << '\n';

    for (size_t i = 0; i < numBombs; i++) {
        sf::Vector2i randomPos;
        do {
            randomPos = getRandomGridPos();
        } while (getTile(randomPos.x, randomPos.y)->isBomb());
        getTile(randomPos.x, randomPos.y)->setBomb();
    };

    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Tile* t = getTile(i, j);

            t->setPos_x(j);
            t->setPos_y(i);
            t->updateRect();
        }
    }
}

Board::~Board(){
    delete[] tiles;
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
                    if (dx == 0 && dy == 0) continue;

                    int nx = i + dx;
                    int ny = j + dy;

                    Tile* neighbour = getTile(nx, ny);
                    if (neighbour != nullptr) {
                        if (neighbour->isBomb()) {
                            bombs++;
                        }
                    }
                }
            }
            currentTile->setValue(bombs);
        }
    }
}
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

    generateBombs();

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

void Board::generateBombs() {
    for (size_t i = 0; i < getSize(); i++) {
        bombs.push_back(&tiles[i]);
    }
    
    while(bombs.size() > numBombs) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> disp(0, bombs.size());
        bombs.erase(bombs.begin() + disp(gen));
    }

    for (Tile* t: bombs) {
        t->setBomb(true);
    }
}
#include "board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

Board::Board(){
    row = 0;
    col = 0;
    tiles = nullptr;
    sm = nullptr;
}

Board::Board(int r, int c, int b){
    row = r;
    col = c;
    numBombs = b;

    tiles = new Tile[row * col];
    sm = new SpriteManager(0);    

    std::cout << "Board created with: \n";
    std::cout << "ROWS: " << row << " COL: " << col << " BOMBS: " << numBombs << '\n';

    generateBombs();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Tile* t = getTile(i, j);

            t->setPos_x(j);
            t->setPos_y(i);
            t->updateSprite(*sm);
        }
    }
}

Board::~Board(){
    delete[] tiles;
    delete sm;
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
                    if (!((nx >= 0 && nx < row) && (ny >= 0 && ny < col))) continue;

                    Tile* neighbour = getTile(nx, ny);
                    if (neighbour != nullptr) {
                        if (neighbour->isBomb()) {
                            bombs++;
                        }
                    }
                }
            }
            currentTile->setOpened(false);
            currentTile->setValue(bombs);
            currentTile->updateSprite(*sm);
        }
    }
}

void Board::generateBombs() {
    for (size_t i = 0; i < getSize(); i++) {
        bombs.push_back(&tiles[i]);
    }
    
    while(bombs.size() > numBombs) {
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> disp(0, bombs.size()-1);
        bombs.erase(bombs.begin() + disp(gen));
    }

    for (Tile* t: bombs) {
        t->setBomb(true);
    }
}

void Board::placeFlag(sf::Vector2f mousePos){
    int x = mousePos.x/9;
    int y = mousePos.y/9;

    Tile* tile = getTile(1,1);
    tile->setFlag(true);
    tile->updateSprite(*sm);
}

void Board::revealTile(sf::Vector2f mousePos){
    int x = mousePos.x/9;
    int y = mousePos.y/9;

    Tile* tile = getTile(1,1);
    tile->setOpened(true);
    tile->updateSprite(*sm);
}
#include "board.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>
#include "tile.h"

Board::Board(){
    row = 0;
    col = 0;
    tiles = nullptr;
    sm = nullptr;
    lost = false;
}

Board::Board(int r, int c, int b){
    row = r;
    col = c;
    numBombs = b;
    lost = false;

    tiles = new Tile[row * col];
    sm = new SpriteManager(0);    

    std::cout << "Board created with: \n";
    std::cout << "ROWS: " << row << " COL: " << col << " BOMBS: " << numBombs << '\n';

    generateBombs();

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            Tile* t = getTile(i, j);

            t->setPos_x(i);
            t->setPos_y(j);
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

            std::vector<Tile*> neighbours;
            getNeighbours(i, j, neighbours);
            for (Tile* tile : neighbours) {
                if (tile->isBomb()) {
                    bombs++;
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

sf::Vector2i Board::handleMouse(sf::Vector2f mousePos) {
    int x = mousePos.x/Tile::getSize();
    int y = mousePos.y/Tile::getSize();
    return sf::Vector2i(x, y);
}

void Board::placeFlag(sf::Vector2i mousePos){
    int x = mousePos.x;
    int y = mousePos.y;
    if (x < 0 || x >= row) return;
    if (y < 0 || y >= col) return;

    Tile* tile = getTile(x,y);
    if (tile->isOpened()) return;
    tile->setFlag(!tile->isFlagged());
    tile->updateSprite(*sm);
}

bool Board::revealTile(sf::Vector2i mousePos, bool clicked){
    int x = mousePos.x;
    int y = mousePos.y;
    if (x < 0 || x >= row) return false;
    if (y < 0 || y >= col) return false;

    Tile* tile = getTile(x,y);
    if (tile->isFlagged()) return false;

    if (tile->isOpened() && clicked) {
        bool hitAbomb = false;
        int numberOfFlags = 0;
        std::vector<Tile*> neighbours;
        getNeighbours(x, y, neighbours);
        for (Tile* neighbour : neighbours) {
            if (neighbour->isFlagged()) numberOfFlags++;
        }
        if (numberOfFlags == tile->getValue()) {
            for (Tile* neighbour : neighbours) {
                if (!neighbour->isOpened()) hitAbomb = revealTile(sf::Vector2i(neighbour->getPos_x(), neighbour->getPos_y()));
                if (hitAbomb) break;
            }
        }
        
        return hitAbomb;
    }

    tile->setOpened(true);

    if (tile->getValue() == 0) {
        std::vector<Tile*> neighbours;
        getNeighbours(x, y, neighbours);
        for (size_t i = 0; i < neighbours.size(); ) {
            if (neighbours[i]->isOpened()) {
                neighbours.erase(neighbours.begin() + i);
            } else {
                i++;
            }
        }

        for (Tile* tile : neighbours) {
            revealTile(sf::Vector2i(tile->getPos_x(), tile->getPos_y()), false);
        }
    }
    tile->updateSprite(*sm);
    if (tile->isBomb()) {
        showBombs();
        return true;
    }

    return false;
}

void Board::getNeighbours(int x, int y, std::vector<Tile*>& neighbours) const {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;
            if (!(nx >= 0 && nx < col && ny >= 0 && ny < row)) continue;

            Tile* neighbour = getTile(nx, ny);
            if (neighbour != nullptr) {
                neighbours.push_back(neighbour);
            }
        }
    }
}

void Board::showBombs() {
    for (Tile* bomb : bombs) {
        if (!bomb->isOpened()) {
            bomb->setOpened(true);
            bomb->updateSprite(*sm, true);
        }
    }
}
#pragma once
#include "board.h"
#include "player.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <string>

class Menu{
    private:
    sf::RectangleShape boxes[3];
    Board* board;
    Player* player;
    float bombDensity = 0.12;
    int rows = 16;
    int columns = 16;

    public:
    Menu();
    ~Menu();
    void drawMenu(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    std::string handleClick(sf::Vector2f mousePos);
    void createBoard(int, int, int);
    void createPlayer();
    Player getPlayer();
    bool isBoard();

};
#pragma once
#include "board.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <string>

class Menu{
    private:
    sf::RectangleShape boxes[3];
    Board* board;
    float bombDensity = 0.12;
    int rows = 16;
    int columns = 16;

    public:
    Menu();
    ~Menu();
    void drawMenu(sf::RenderWindow &window);
    void drawBoard(sf::RenderWindow &window);
    Board* createBoard(int, int, int);

};
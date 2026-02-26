#pragma once
#include "board.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Menu{
    private:
    Board* board;

    public:
    Menu();
    ~Menu();
    void drawMenu();
    void createBoard(int, int, int);

};
#pragma once
#include "board.h"
#include <iostream>
#include <string>

class Menu{
    private:
    Board* board;

    public:
    Menu();
    ~Menu();
    void drawMenu();
    void createBoard(int, int);

};
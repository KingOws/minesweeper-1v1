#pragma once
#include "board.h"
#include "player.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <string>

class Player;  // Forward declare Player

class Menu{
    private:
    sf::RectangleShape boxes[3];
    sf::Font font;
    sf::Text textFields[3];
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
    std::string setDifficulty(sf::Vector2f mousePos);
    void createBoard(int, int, int);
    void createPlayer();

    inline Player* getPlayer(){return player;};
    inline Board* getBoard(){return board;};
    inline bool isBoard(){
        if(board == nullptr)
            return false;
        return true;
    }

};
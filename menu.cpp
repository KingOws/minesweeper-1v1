#include "menu.h"


Menu::Menu(){
    board = nullptr;
}

Menu::~Menu(){

}

void Menu::drawMenu(sf::RenderWindow &window){

    if (board != nullptr) {
        board->updateBoard();
    }
    
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        if (board != nullptr) {
            board->updateBoard();
            board->drawBoard(window);
        }

        window.display();
    }
}

void Menu::createBoard(int r, int c, int b){
    board = new Board(r,c,b);
}
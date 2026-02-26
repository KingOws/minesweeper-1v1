#include "menu.h"


Menu::Menu(){
    board = nullptr;
}

Menu::~Menu(){

}

void Menu::drawMenu(){
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Works!");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}

void Menu::createBoard(int r, int c){
    board = new Board(r,c);
}
#include "menu.h"


Menu::Menu(){
    board = nullptr;
    float posx = 100, posy = 150;
    
    for(sf::RectangleShape &rect : boxes){
        rect.setSize({600,100});
        rect.setFillColor({75,175,75,75});
        rect.setPosition({posx, posy});
        posy += 150;
    }
}

Menu::~Menu(){

}

void Menu::drawMenu(sf::RenderWindow &window){
    if(board == nullptr){
        for(sf::RectangleShape &rect : boxes){
            window.draw(rect);
        }
    }else{
        board->drawBoard(window);
    }
}


std::string Menu::handleClick(sf::Vector2f mousePos){
    if(boxes[0].getGlobalBounds().contains(mousePos))
        return "easy";
    if(boxes[1].getGlobalBounds().contains(mousePos))
        return "medium";
    if(boxes[2].getGlobalBounds().contains(mousePos))
        return "hard";

    return "";
}

void Menu::createBoard(int r, int c, int b){
    board = new Board(r,c,b);
}

#include "menu.h"
#include <SFML/Graphics.hpp>

Menu::Menu() : textFields{sf::Text(font), sf::Text(font), sf::Text(font)} {
    board = nullptr;
    if (!font.openFromFile("../fonts/arial.ttf")) {
        std::cerr << "Error: could not load font" << std::endl;
    }

    float posx = 100, posy = 150;
    
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape& rect = boxes[i];
        sf::Text& text = textFields[i];
        rect.setSize({600,100});
        rect.setFillColor({75,175,75,75});
        rect.setPosition({posx, posy});
        posy += 150;

        switch(i) {
            case 0:
            text.setString("Easy");
            break;
            case 1:
            text.setString("Medium");
            break;
            case 2:
            text.setString("Hard");
            break;
        }

                text.setFont(font);
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);

        // Center text inside the rect
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                        textBounds.position.y  + textBounds.size.y / 2.f});
        text.setPosition({rect.getPosition().x + rect.getSize().x / 2.f,
                        rect.getPosition().y + rect.getSize().y / 2.f});
    }
}

Menu::~Menu(){

}

void Menu::drawMenu(sf::RenderWindow &window){
    if(board == nullptr){
        for(sf::RectangleShape &rect : boxes){
            window.draw(rect);
        }
        for(sf::Text &text : textFields){
            window.draw(text);
        }
    }
    else{
        board->drawBoard(window);
    }
}


std::string Menu::setDifficulty(sf::Vector2f mousePos){
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
    board->updateBoard();
}

void Menu::createPlayer(){
    player = new Player();
}

void Menu::checkGameWon(){
    for(int i = 0; i < board->getCol(); i++){
        for(int j = 0; j < board->getRow(); j++){
            if(!board->getTile(i,j)->isOpened() && !board->getTile(i,j)->isBomb()){
                return;
            }
        }
    }
    board->setWon(true);
    delete board;
    board = nullptr;
    std::cout << "Winner winner chicken dinner!";
    return;
}




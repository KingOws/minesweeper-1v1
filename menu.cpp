#include "menu.h"

Menu::Menu(){
    board = nullptr;
}

Menu::~Menu(){

}

void Menu::drawMenu(){

}

void Menu::createBoard(int r, int c){
    board = new Board(r,c);
}
#include "minesweeper.h"

//std
#include <iostream>

Minesweeper::Minesweeper() : m_isRunning(true){
    initWindow();
}

void Minesweeper::run(){
    while(window.isOpen()){
        handleEvents();
        update();
        display();
    }
}

void Minesweeper::update(){
    updateNetManager();
    updateScManager();
    updateSpriteManager();
}
void Minesweeper::display(){
    window.clear();
    sceneManager.displayScene(window);
    window.display();
}


void Minesweeper::handleEvents(){
    while(auto event = window.pollEvent()){
        const sf::Event& e = *event;
        if (event->is<sf::Event::Closed>()){
            window.close();
        }
        sceneManager.handleEvent(*event);
    }
}

void Minesweeper::updateScManager(){

}

void Minesweeper::updateNetManager(){

}

void Minesweeper::updateSpriteManager(){

}

void Minesweeper::initWindow(){
    if (!icon.loadFromFile("../images/icon.png")) {
        std::cerr << "Failed to load icon.png" << std::endl;
    }
    window.setIcon(icon);
}
#include "minesweeper.h"

//std
#include <iostream>

Minesweeper::Minesweeper() : m_isRunning(true), gameState(GAMESTATE::MENU){
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
    updateScManager();
    if(updateNetManager()) return;
    createNetManager();
}

void Minesweeper::createNetManager(){
    if(gameState == GAMESTATE::JOINING_WAITING)
        networkManager = std::make_unique<NetworkManager>();

    if(gameState == GAMESTATE::HOSTING_WAITING)
        networkManager = std::make_unique<NetworkManager>();
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
        sceneManager.handleEvent(*event, gameState);
    }
}

void Minesweeper::updateScManager(){
    if(isMultiplayer(gameState)) 
        sceneManager.update(networkInfo);
    else 
        sceneManager.update();
}

bool Minesweeper::updateNetManager(){
    if (gameState == GAMESTATE::MENU || gameState == GAMESTATE::SP_PLAYING) {
        if (networkManager)
            networkManager.reset(); 
    }

    if(networkManager){
        networkManager->update(networkInfo);
        return true;
    }
    return false;
}

void Minesweeper::initWindow(){
    if (!icon.loadFromFile("../images/icon.png")) {
        std::cerr << "Failed to load icon.png" << std::endl;
    }
    window.setIcon(icon);
}

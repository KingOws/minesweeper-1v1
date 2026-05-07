#include "game.h"


int Game::idGen = 0;
Game::Game(){
    idGen++;
    gameId = idGen;
    std::cout << "Created game with Id: " << gameId << std::endl;
}

Game::~Game(){
    idGen--;
}


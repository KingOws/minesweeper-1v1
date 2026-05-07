#include "player.h"


int Player::idGen = 0;
Player::Player(){
    idGen++;
    playerId = idGen;
    std::cout << "Player created with Id: " << playerId << std::endl;
}

Player::~Player(){
    idGen--;
}

Player::Player(std::unique_ptr<sf::TcpSocket> pendingSocket, LobbyInfo& lobbyInfo, bool isA){
    idGen++;
    playerId = idGen;

    isAuth = isA;
    info = lobbyInfo;
    socket = std::move(pendingSocket);

    info.playerId = playerId;
    std::cout << "Player created with Id: " << playerId << std::endl;
}



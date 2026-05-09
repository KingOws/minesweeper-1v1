#include "lobbyhosting.h"


LobbyHosting::LobbyHosting(){
    hosting = true;
    lobbyInfo.currentPlayers = 1;
    lobbyInfo.playerId = 1;
    
    listener.listen(PORT);
    selector.add(listener);
}

void LobbyHosting::establishConnection(){
    if(selector.wait(sf::milliseconds(10))){
        if(selector.isReady(listener)){
            auto newSocket = std::make_unique<sf::TcpSocket>();
            if(listener.accept(*newSocket) == sf::Socket::Status::Done){
                if(lobbyInfo.currentPlayers >= lobbyInfo.maxPlayers || lobbyInfo.inGame){
                    std::cout << "Lobby full or in game, rejecting client" << std::endl;
                    newSocket->disconnect();
                } else {
                    std::cout << "Client connected: " << newSocket->getRemoteAddress().value() << std::endl;
                    newSocket->setBlocking(false);
                    selector.add(*newSocket);
                    clientList.push_back(std::move(newSocket));
                    lobbyInfo.currentPlayers++;
                }
            }
        }
    }
}


void LobbyHosting::shutdown(){
    for(auto& client : clientList){
        selector.remove(*client);
        client->disconnect();
    }
    clientList.clear();
    selector.remove(listener);
    listener.close();
    listener = sf::TcpListener{};
    hosting = false;
}


LobbyHosting::~LobbyHosting() {
    if (hosting) shutdown();
}
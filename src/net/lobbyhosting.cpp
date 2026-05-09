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

void LobbyHosting::sendPackets(){
    for (const std::unique_ptr<sf::TcpSocket>& client: clientList) {
        client->setBlocking(false);
        if(packet.getDataSize() == 0) return;

        sf::Socket::Status status;
        do {
            status = client->send(packet);
        } while(status == sf::Socket::Status::NotReady);
        
        if(status == sf::Socket::Status::Done){
            std::cout << "Package Sent to " << client->getRemoteAddress()->toString() << "!\n";
            packet.clear();
        } else if(status == sf::Socket::Status::Error){
            std::cerr << "Big error\n";
        }
    }
}

void LobbyHosting::receivePackets(){
    for (const std::unique_ptr<sf::TcpSocket>& client: clientList) {
        client->setBlocking(false);
        sf::Socket::Status status = socket->receive(packet);
        if(status == sf::Socket::Status::Done){
            std::cout << "Received from " << client->getRemoteAddress()->toString() << '\n';
        }
    }
}
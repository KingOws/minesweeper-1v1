#include "lobbyhosting.h"


LobbyHosting::LobbyHosting() : Lobby(){
    broadcastTimer.start();
    hosting = true;
    lobbyInfo.inGame = false;
    
    sf::Socket::Status status = listener.listen(GAME_PORT);
    if(status == sf::Socket::Status::Done){
        std::cout << "Host is listening on port " << GAME_PORT << std::endl;
        selector.add(listener);
    }
    else if(status == sf::Socket::Status::Error)
        std::cout << "Error adding listener to gameport";
}

void LobbyHosting::establishConnection(std::atomic<bool>&  running){
    //if (isPlayerIPEmpty()) return;
    this->runServer();

    if(lobbyInfo.currentPlayers < lobbyInfo.maxPlayers){
        sf::Packet beacon;
        //sends a beacon signal using broadcast address basically letting everyone know what the host address is
        if(broadcastTimer.getElapsedTime() > sf::seconds(1.0f)){
            udpListener.send(beacon, sf::IpAddress::Broadcast, DiscoveryPort);
            broadcastTimer.restart();
        }
    }   
}

void LobbyHosting::runServer(){
    if(selector.wait(sf::milliseconds(10))){
        if(selector.isReady(listener)){
            auto newSocket = std::make_unique<sf::TcpSocket>();

            if(listener.accept(*newSocket) == sf::Socket::Status::Done){

                if(lobbyInfo.currentPlayers >= lobbyInfo.maxPlayers || lobbyInfo.inGame){
                    std::cout << "Lobby full or in game, rejecting client" << std::endl;
                    newSocket->disconnect();

                } else {
                    std::cout << "Client connected: " << newSocket->getRemoteAddress().value() << std::endl;
                    PlayerInfo newPlayer;
                    newPlayer.playerId = lobbyInfo.currentPlayers;
                    newPlayer.socket = std::move(newSocket);
                    selector.add(*newPlayer.socket);
                    //also has to be move because it contains socket yuck
                    players.push_back(std::move(newPlayer));
                    lobbyInfo.currentPlayers++;
                    tcpLinkReady = true;
                }
            }
        }
    }
}


void LobbyHosting::shutdown(){
    for(auto& player : players){
        selector.remove(*player.socket);
        player.socket->disconnect();
    }
    players.clear();
    selector.remove(listener);
    listener.close();
    listener = sf::TcpListener{};
    hosting = false;
}


LobbyHosting::~LobbyHosting() {
    if (hosting) shutdown();
}

void const LobbyHosting::sendPackets(){
    if(packet.getDataSize() == 0) return;
    for (auto it = players.begin(); it != players.end(); it++) {


        sf::Socket::Status status = it->socket->send(packet);
        packet.clear();

        if(status == sf::Socket::Status::Done)
            std::cout << "Package Sent to " << it->socket->getRemoteAddress()->toString() << "!\n";
        else if(status == sf::Socket::Status::Error)
            std::cerr << "Big error\n";
    }
}

void const LobbyHosting::receivePackets(){
    for (auto it = players.begin(); it != players.end();) {
        if (selector.isReady(*(it->socket))) {
            sf::Socket::Status status = it->socket->receive(packet);

            if (status == sf::Socket::Status::Done) {
                if(lobbyInfo.inGame == true){
                    std::cout << "Received from " << it->socket->getRemoteAddress()->toString() << '\n';



                    handlePlayerPackets((*it));
                    packet.clear();
                    ++it;
                }
            } else if (status == sf::Socket::Status::Disconnected || status == sf::Socket::Status::Error) {
                lobbyInfo.currentPlayers--;
                std::cout << "Client disconnected: " << it->socket->getRemoteAddress()->toString() << '\n';
                selector.remove(*(it->socket));
                it = players.erase(it);
            }else
                ++it;
        }else
            ++it;
    }
}

void const LobbyHosting::handlePlayerPackets(PlayerInfo& player){

}
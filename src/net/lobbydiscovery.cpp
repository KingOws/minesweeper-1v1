#include "lobbydiscovery.h"

LobbyDiscovery::LobbyDiscovery(GameInfo &g) : gameInfo(g), connected(false){
    std::cout << "Attempting to Connect: ";
    socket.setBlocking(true);
    auto status = socket.connect(serverAddress, 55001);

    if(status == sf::Socket::Status::Done){
        connected = true;
        socket.setBlocking(false);
        std::cout << "Connected!" << std::endl;
        updatePackets();
        sendPackets();
    }else
        std::cerr << "Connection failed or timed out." << std::endl;

}

void LobbyDiscovery::sendPackets(){
    if(packet.getDataSize() == 0) return;

    sf::Socket::Status status = socket.send(packet);
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Sent!" << std::endl;
        packet.clear();
    }else if(status == sf::Socket::Status::Error){
        std::cerr << "Big error" << std::endl;
    }
}

void LobbyDiscovery::receivePackets(){

}

void LobbyDiscovery::updatePackets(){
    packet.clear();
    packet << gameInfo.hosting << gameInfo.gameCreated << gameInfo.playerCount;
}

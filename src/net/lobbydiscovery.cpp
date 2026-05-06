#include "lobbydiscovery.h"

LobbyDiscovery::LobbyDiscovery(LobbyInfo &g) : lobbyInfo(g), connected(false){
    std::cout << "Attempting to Connect: ";
    socket.setBlocking(true);
    auto status = socket.connect(serverAddress, 55001);

    if(status == sf::Socket::Status::Done){
        connected = true;
        socket.setBlocking(false);
        std::cout << "Connected!" << std::endl;
        updatePackets();
        sendPackets();
        receivePackets();
    }else
        std::cerr << "Connection failed or timed out." << std::endl;

}

void LobbyDiscovery::sendPackets(){
    socket.setBlocking(false);
    if(packet.getDataSize() == 0) return;

    sf::Socket::Status status;
    do {
        status = socket.send(packet);
    } while(status == sf::Socket::Status::NotReady);
    
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Sent!" << std::endl;
        packet.clear();
    } else if(status == sf::Socket::Status::Error){
        std::cerr << "Big error" << std::endl;
    }
}

void LobbyDiscovery::receivePackets(){
    socket.setBlocking(false);
    sf::Socket::Status status = socket.receive(packet);
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Received!" << std::endl;
        packet >> lobbyInfo;
        packet.clear();
    }
}

void LobbyDiscovery::updatePackets(){
    packet.clear();
    packet << lobbyInfo;
}

#include "Lobby.h"

//Set Ip Address
Lobby::Lobby() {
    udpListener.setBlocking(false);
    socket->setBlocking(false);
    std::optional<sf::IpAddress> localIp = sf::IpAddress::getLocalAddress();
    if (localIp.has_value()) {
        std::cout << "My IP: " << localIp->toString() << std::endl;
        playerAddress = *localIp;
    }else{
        std::cout << "You are not connected to the internet";
    }
}


//  Send Packets for the Game
void Lobby::sendPackets(){
    if(packet.getDataSize() == 0) return;

    sf::Socket::Status status;
    do {
        status = socket->send(packet);
    } while(status == sf::Socket::Status::NotReady);
    
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Sent!" << std::endl;
        packet.clear();
    } else if(status == sf::Socket::Status::Error){
        std::cerr << "Big error" << std::endl;
    }
}

//  Receive Packets for the Game
void Lobby::receivePackets(){
    sf::Socket::Status status = socket->receive(packet);
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Received!" << std::endl;
        packet >> lobbyInfo;
        packet.clear();
    }
}

// Update Packets
void Lobby::updatePackets(){
    packet.clear();
    packet << lobbyInfo;
}

void Lobby::disconnect() {
    if (tcpLinkReady) {
        socket->disconnect();
        tcpLinkReady = false;
        hosting = false;
        remoteAddress = sf::IpAddress::Any;
        packet.clear();
        std::cout << "Disconnected.\n";
    }
}

Lobby::~Lobby() {}
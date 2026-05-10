#include "Lobby.h"

//Set Ip Address
Lobby::Lobby() {
    udpListener.setBlocking(false);
    socket->setBlocking(false);
    tcpLinkReady = false;
    connected = false;
    hosting = false;
    std::optional<sf::IpAddress> localIp = sf::IpAddress::getLocalAddress();
    if (localIp.has_value()) {
        std::cout << "My IP: " << localIp->toString() << std::endl;
        playerAddress = *localIp;
    }else{
        std::cout << "You are not connected to the internet";
    }
}

void Lobby::disconnect() {
    socket->disconnect();
    tcpLinkReady = false;
    hosting = false;
    remoteAddress = sf::IpAddress::Any;
    packet.clear();
    std::cout << "Disconnected.\n";

}

Lobby::~Lobby() {}
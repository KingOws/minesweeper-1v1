#include "lobbydiscovery.h"
#include <atomic>

LobbyDiscovery::LobbyDiscovery() : Lobby() {
    if(udpListener.bind(DiscoveryPort) == sf::Socket::Status::Done)
        std::cout << "Joining is listening on UDP" << std::endl;
    hosting = false;
    connected = false;
}

void LobbyDiscovery::establishConnection(std::atomic<bool>&  running) {
    if (isPlayerIPEmpty() || tcpLinkReady) return;

    if(!connected){
        this->findServer();
    }else{

        sf::Socket::Status status = socket->connect(remoteAddress, GAME_PORT, sf::seconds(2));
        if(status == sf::Socket::Status::Done){
            std::cout << "Succesfully connected to minesweeper!\n";
            tcpLinkReady = true;
        }else if(status == sf::Socket::Status::Error){
            std::cout << "Failed to connected to host!\n";
            connected = false;
        }
    }
}

void LobbyDiscovery::findServer(){
    sf::Packet receiver;
    std::optional<sf::IpAddress> senderIp;
    unsigned short senderPort;

    //receive modifies the remoteAddress to the address of whomever sent the packet
    if(udpListener.receive(receiver, senderIp, senderPort) == sf::Socket::Status::Done){
        if(senderIp){
            std::cout << "Obtained Server Address: " << senderIp->toString() << std::endl;
            this->remoteAddress = *senderIp;
            this->connected = true;
        }
    }
}


LobbyDiscovery::~LobbyDiscovery() {}

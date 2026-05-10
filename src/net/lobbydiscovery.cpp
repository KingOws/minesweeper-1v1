#include "lobbydiscovery.h"
#include <atomic>

LobbyDiscovery::LobbyDiscovery() : Lobby() {
    if(udpListener.bind(DiscoveryPort) == sf::Socket::Status::Done)
        std::cout << "Joining is listening on UDP" << std::endl;
    hosting = false;
}

void LobbyDiscovery::establishConnection(std::atomic<bool>& running) {
    if (isPlayerIPEmpty() || tcpLinkReady) return;

    if (!connected) {
        this->findServer();
    } else {
        socket->setBlocking(true);
        sf::Socket::Status status = socket->connect(remoteAddress, GAME_PORT, sf::seconds(2));
        if (status == sf::Socket::Status::Done) {
            std::cout << "Successfully connected to host!\n";
            tcpLinkReady = true;
            connected = true;
            udpListener.unbind(); // Stop listening for the beacon
        } else {
            std::cout << "Failed to connect. Retrying discovery.\n";
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

//  Receive Packets for the Game
void const LobbyDiscovery::receivePackets(){
    sf::Socket::Status status = socket->receive(packet);
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Received!" << std::endl;


        packet.clear();
    }
}

//  Send Packets for the Game
void const LobbyDiscovery::sendPackets(){
    if(packet.getDataSize() == 0) return;
    updatePackets();
    sf::Socket::Status status = socket->send(packet);    
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Sent!" << std::endl;
        packet.clear();
    } else if(status == sf::Socket::Status::Disconnected){
        disconnect();
    }
}

// Update Packets
void const LobbyDiscovery::updatePackets(){
    packet.clear();

}

LobbyDiscovery::~LobbyDiscovery() {}

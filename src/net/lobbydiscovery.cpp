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
void LobbyDiscovery::receivePackets(){
    sf::Socket::Status status = socket->receive(packet);
    if(status == sf::Socket::Status::Done){
        //std::cout << "Package Received!" << std::endl;
        switch(playerAction.inGame){
            case false:
                packet >> lobbyInfo;
                packet >> playerAction;
                break;
            case true:
                packet >> gameUpdate;
                packet >> playerAction;
                break;
        }
        packet.clear();
    }
}

//  Send Packets for the Game
void LobbyDiscovery::sendPackets(){
    packet.clear();
    switch(playerAction.inGame){
        //I can't think of a reason as to why the client would saend smth to host in lboby but leaving it here just in case
        case false:
            break;
        case true:
            packet << playerAction;
            break;
    }

    if(packet.getDataSize() == 0) return;
    sf::Socket::Status status = socket->send(packet);    
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Sent!" << std::endl;
    } else if(status == sf::Socket::Status::Disconnected){
        disconnect();
    }
}


void LobbyDiscovery::updatePackets(){
    if(gameUpdate.won)
        std::cout << "Joiner won!" << std::endl;
    else if(gameUpdate.lost)
        std::cout << "Joiner lost!" << std::endl;
}

LobbyDiscovery::~LobbyDiscovery() {}

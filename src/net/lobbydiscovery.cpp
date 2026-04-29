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
    if(packet.getDataSize() == 0) return;

    sf::Socket::Status status = socket.receive(packet);
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Received!" << std::endl;
    }
    packet >> lobbyInfo.hosting >> lobbyInfo.gameCreated >> lobbyInfo.lobbyId >> lobbyInfo.currentPlayers >> lobbyInfo.maxPlayers >> lobbyInfo.availableGames;
    packet.clear();
}

void LobbyDiscovery::updatePackets(){
    packet.clear();
    packet << lobbyInfo.hosting << lobbyInfo.gameCreated << lobbyInfo.lobbyId << lobbyInfo.currentPlayers << lobbyInfo.maxPlayers << lobbyInfo.availableGames;
}

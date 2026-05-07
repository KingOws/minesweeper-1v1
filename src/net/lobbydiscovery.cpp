#include "lobbydiscovery.h"


// Find Connections???
LobbyDiscovery::LobbyDiscovery(LobbyInfo &g) : lobbyInfo(g), connected(false){
    std::optional<sf::IpAddress> localIp = sf::IpAddress::getLocalAddress();
    if (localIp.has_value()) {
        std::cout << "My IP: " << localIp->toString() << std::endl;
        localAddress = *localIp;
    }
}


//  Send Packets for the Game
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

//  Receive Packets for the Game
void LobbyDiscovery::receivePackets(){
    socket.setBlocking(false);
    sf::Socket::Status status = socket.receive(packet);
    if(status == sf::Socket::Status::Done){
        std::cout << "Package Received!" << std::endl;
        packet >> lobbyInfo;
        packet.clear();
    }
}

// Update Packets????
void LobbyDiscovery::updatePackets(){
    packet.clear();
    packet << lobbyInfo;
}


void LobbyDiscovery::startServer() {
    listener.listen(PORT);
    std::cout << "Hosting on port " << PORT << "\n";
    hosting = true;
    
    // Block until a client connects
    if (listener.accept(socket) == sf::Socket::Status::Done) {
        std::cout << "Client connected!\n";
        connected = true;
        remoteAddress = *socket.getRemoteAddress();
    }
}


void LobbyDiscovery::findServer() {
    std::optional<sf::IpAddress> localIp = sf::IpAddress::getLocalAddress();
    if (localIp.has_value()) {
        std::cout << "My IP: " << localIp->toString() << std::endl;
        localAddress = *localIp;
    } else return;

    std::string base = localAddress.toString();
    // Strip last octet to get subnet base e.g. "192.168.1."
    std::string subnet = base.substr(0, base.rfind('.') + 1);
    socket.setBlocking(true);

    for (int i = 1; i < 255; i++) {
        std::string ip = subnet + std::to_string(i);
        
        // Skip own IP
        if (ip == base) continue;

        socket.disconnect();
        remoteAddress = *sf::IpAddress::resolve(ip);
        std::cout << "Trying IP: " << ip << '\n';
        sf::Socket::Status status = socket.connect(remoteAddress, PORT, sf::milliseconds(50));
        
        if (status == sf::Socket::Status::Done) {
            std::cout << "Found host at: " << ip << '\n';
            connected = true;
            socket.setBlocking(false);
            break;
        }
    }
    if (!socket.getRemoteAddress().has_value())
        std::cerr << "No Host \n";
}

void LobbyDiscovery::disconnect() {
    if (connected) {
        socket.disconnect();
        connected = false;
        hosting = false;
        remoteAddress = sf::IpAddress::Any;
        packet.clear();
        std::cout << "Disconnected.\n";
    }
}

LobbyDiscovery::~LobbyDiscovery() {
    disconnect();
    listener.close();
}
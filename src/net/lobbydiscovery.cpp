#include "lobbydiscovery.h"

LobbyDiscovery::LobbyDiscovery() {
    hosting = false;
}

void LobbyDiscovery::findServer() {
    if (scanned) return;
    scanned = true;
    
    std::optional<sf::IpAddress> localIp = sf::IpAddress::getLocalAddress();
    if (localIp.has_value()) {
        std::cout << "My IP: " << localIp->toString() << std::endl;
        playerAddress = *localIp;
    } else return;

    std::string base = playerAddress.toString();
    // Strip last octet to get subnet base e.g. "192.168.1."
    std::string subnet = base.substr(0, base.rfind('.') + 1);
    socket->setBlocking(true);

    for (int i = 1; i < 255; i++) {
        std::string ip = subnet + std::to_string(i);
        
        // Skip own IP
        if (ip == base) continue;

        socket->disconnect();
        remoteAddress = *sf::IpAddress::resolve(ip);
        std::cout << "Trying IP: " << ip << '\n';
        sf::Socket::Status status = socket->connect(remoteAddress, PORT, sf::milliseconds(50));
        
        if (status == sf::Socket::Status::Done) {
            std::cout << "Found host at: " << ip << '\n';
            connected = true;
            socket->setBlocking(false);
            break;
        }
    }
    if (!socket->getRemoteAddress().has_value())
        std::cerr << "No Host \n";
}


LobbyDiscovery::~LobbyDiscovery() {}
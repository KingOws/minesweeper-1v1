#include "lobbydiscovery.h"

LobbyDiscovery::LobbyDiscovery() {
    hosting = false;
    connected = false;

    std::optional<sf::IpAddress> localIp = sf::IpAddress::getLocalAddress();
    if (localIp.has_value()) {
        std::cout << "My IP: " << localIp->toString() << std::endl;
        playerAddress = *localIp;
    } else return;
}

void LobbyDiscovery::establishConnection() {
    if (isPlayerIPEmpty() || connected) return;

    std::string base = playerAddress.toString();
    std::string subnet = base.substr(0, base.rfind('.') + 1);

    for (int i = 1; i < 255; i++) {
        std::string ip = subnet + std::to_string(i);
        if (ip == base) continue;

        std::optional<sf::IpAddress>  resolved = sf::IpAddress::resolve(ip);
        if (!resolved.has_value()) continue; 

        sf::TcpSocket tempSocket;
        tempSocket.setBlocking(true);

        if (tempSocket.connect(*resolved, PORT, sf::milliseconds(50)) == sf::Socket::Status::Done) {
            std::cout << "Found host at: " << ip << '\n';
            socket->setBlocking(false);
            *socket = std::move(tempSocket);
            connected = true;
            break;
        }
    }

    if (!connected)
        std::cerr << "No Host\n";
}


LobbyDiscovery::~LobbyDiscovery() {}

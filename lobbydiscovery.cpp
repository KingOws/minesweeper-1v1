#include "lobbydiscovery.h"
#include <optional>

void LobbyDiscovery::bindForListening() {
    socket.setBlocking(false);
    socket.bind(BROADCAST_PORT);
}

void LobbyDiscovery::broadcastPresence(unsigned short gamePort) {
    sf::Packet packet;
    packet << std::string(MAGIC) << sf::IpAddress::getLocalAddress().value().toString() << gamePort;
    socket.send(packet, sf::IpAddress::Broadcast, BROADCAST_PORT);
}

bool LobbyDiscovery::pollForHosts(HostEntry& out) {
    sf::Packet packet;
    std::optional<sf::IpAddress> sender;
    unsigned short senderPort;
    if (socket.receive(packet, sender, senderPort) == sf::Socket::Status::Done) {
        std::string magic;
        packet >> magic;
        if (magic == MAGIC) {
            packet >> out.ip >> out.gamePort;
            out.lastSeen.restart();
            return true;
        }
    }
    return false;
}

void LobbyDiscovery::pruneStaleHosts(std::vector<HostEntry>& hosts) {

}

void LobbyDiscovery::upsertHost(std::vector<HostEntry>& hosts, HostEntry& entry) {

}
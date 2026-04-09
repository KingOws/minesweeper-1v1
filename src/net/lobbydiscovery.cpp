#include "lobbydiscovery.h"
#include <optional>
#include <algorithm>

LobbyDiscovery::LobbyDiscovery(Role role, unsigned short gamePort) : role(role), gamePort(gamePort){
    socket.setBlocking(false);
    if (role == Role::Joiner)
        socket.bind(BROADCAST_PORT);
}

std::unique_ptr<LobbyDiscovery> LobbyDiscovery::createHost(unsigned short gamePort) {
    return std::unique_ptr<LobbyDiscovery>(new LobbyDiscovery(Role::Host, gamePort));
}

std::unique_ptr<LobbyDiscovery> LobbyDiscovery::createJoiner() {
    return std::unique_ptr<LobbyDiscovery>(new LobbyDiscovery(Role::Joiner));
}

void LobbyDiscovery::tick(std::vector<HostEntry>& hosts) {
    if (role == Role::Host) {
        broadcastPresence();
    } else {
        pruneStaleHosts(hosts);
        HostEntry entry;
        if (pollForHosts(entry))
            upsertHost(hosts, entry);
    }
}

void LobbyDiscovery::broadcastPresence() {
    sf::Packet packet;
    packet << std::string(MAGIC) 
           << sf::IpAddress::getLocalAddress().value().toString() 
           << gamePort;
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
    constexpr float STALE_THRESHOLD_SECONDS = 5.0f;
    hosts.erase(
        std::remove_if(hosts.begin(), hosts.end(), [](const HostEntry& h) {
            return h.lastSeen.getElapsedTime().asSeconds() > STALE_THRESHOLD_SECONDS;
        }),
        hosts.end()
    );
}

void LobbyDiscovery::upsertHost(std::vector<HostEntry>& hosts, HostEntry& entry) {
    for (HostEntry& h : hosts) {
        if (h.ip == entry.ip && h.gamePort == entry.gamePort) {
            h.lastSeen.restart();
            return;
        }
    }
    hosts.push_back(entry);
}
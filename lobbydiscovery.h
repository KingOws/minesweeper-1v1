#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <vector>

struct HostEntry {
    std::string ip;
    unsigned short gamePort;
    sf::Clock lastSeen;
};

class LobbyDiscovery {
    sf::UdpSocket socket;
    static constexpr unsigned short BROADCAST_PORT = 6767;
    static constexpr const char* MAGIC = "MINESWEEPER_HOST";

public:
    void bindForListening();
    void broadcastPresence(unsigned short gamePort);
    bool pollForHosts(HostEntry& out);
    void pruneStaleHosts(std::vector<HostEntry>& hosts);
    void upsertHost(std::vector<HostEntry>& hosts, HostEntry& entry);
};
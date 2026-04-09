#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>

struct HostEntry {
    std::string ip;
    unsigned short gamePort;
    sf::Clock lastSeen;
};

class LobbyDiscovery {
public:
    static std::unique_ptr<LobbyDiscovery> createHost(unsigned short gamePort);
    static std::unique_ptr<LobbyDiscovery> createJoiner();
    void tick(std::vector<HostEntry>& hosts);

private:
    enum class Role { Host, Joiner };
    LobbyDiscovery(Role role, unsigned short gamePort = 0);

    void broadcastPresence();
    bool pollForHosts(HostEntry& out);
    void pruneStaleHosts(std::vector<HostEntry>& hosts);
    void upsertHost(std::vector<HostEntry>& hosts, HostEntry& entry);

    static constexpr unsigned short BROADCAST_PORT = 6767;
    static constexpr const char* MAGIC = "MINESWEEPER_HOST";

    sf::UdpSocket socket;
    Role role;
    unsigned short gamePort;
};
#pragma once
#include "net/NetworkInfo.h"

#include <SFML/Network.hpp>
#include <memory>
#include <vector>
struct NetworkInfo;

enum class NetMode {
  NONE,
  SERVER,
  CLIENT
};

class NetworkManager{
    public: 
    NetMode mode = NetMode::NONE;

    //DISCOVERY
    sf::UdpSocket udp;
    sf::Clock broadcastClock; 
    //Server Side
    sf::TcpListener listener;
    sf::SocketSelector selector;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;

    // Client Side
    sf::TcpSocket socket;
    std::optional<sf::IpAddress> serverIp;

    void update(NetworkInfo& networkInfo);

    void startServer();
    void startClient();

    private:
    NetworkManager();

    void discoveryPing();

    void updateServer(NetworkInfo& networkInfo);
    void updateClient(NetworkInfo& networkInfo);

    void sendInfo();
    void receiveInfo();
};

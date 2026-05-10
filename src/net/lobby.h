#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "IScene.h"
#include "board.h"


class Lobby {
    protected:
        unsigned short GAME_PORT = 55001;
        std::unique_ptr<sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();

        unsigned short DiscoveryPort = 49152;
        sf::UdpSocket udpListener;

        sf::Packet packet;
        sf::IpAddress playerAddress{192,168,0,0};
        sf::IpAddress remoteAddress{192,168,0,255};
        bool hosting;
        bool connected;
        bool tcpLinkReady;

    public:
        Lobby();
        ~Lobby();

        bool isPlayerIPEmpty() {if (playerAddress == sf::IpAddress{192,168,0,0}) return true; return false;};
        
        virtual void establishConnection(std::atomic<bool>&  running) {};
        virtual void disconnect();
        virtual void updatePackets() {};
        virtual void sendPackets() {};
        virtual void receivePackets() {};
        virtual bool isConnected() const {return connected;};
};
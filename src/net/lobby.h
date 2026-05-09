#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "IScene.h"

class Lobby {
    protected:
        int PORT = 55001;
        std::unique_ptr<sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();
        sf::Packet packet;
        LobbyInfo lobbyInfo;
        sf::IpAddress playerAddress{192,168,0,0};
        sf::IpAddress remoteAddress{192,168,0,0};
        bool hosting;
        bool connected;

    public:
        Lobby();
        ~Lobby();

        bool isPlayerIPEmpty() {if (playerAddress == sf::IpAddress{192,168,0,0}) return true; return false;};
        
        virtual void establishConnection() {};
        virtual void disconnect();
        virtual void updatePackets();
        virtual void sendPackets();
        virtual void receivePackets();
        virtual bool isConnected() const {return connected;};
        virtual LobbyInfo& getGameInfo() {return lobbyInfo;};
};
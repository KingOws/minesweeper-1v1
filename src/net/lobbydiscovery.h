#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "IScene.h"

class LobbyDiscovery {
    private:
        int PORT = 55001;
        sf::TcpSocket socket;
        sf::TcpListener listener;
        sf::Packet packet;
        LobbyInfo& lobbyInfo;
        sf::IpAddress localAddress{192,168,0,0};
        sf::IpAddress remoteAddress{192,168,0,0};
        bool hosting;
        bool connected;

    public:
        LobbyDiscovery(LobbyInfo&);
        ~LobbyDiscovery();
        
        void disconnect();
        
        void updatePackets();
        void sendPackets();
        void receivePackets();

        void startServer();
        void findServer();

        bool isConnected() const {return connected;};

        void getGameInfo();


   
};
#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "IScene.h"

class LobbyDiscovery {
    private:
        sf::TcpSocket socket;
        sf::Packet packet;
        LobbyInfo& lobbyInfo;
        sf::IpAddress serverAddress{192,168,1,80};
        bool connected;

    public:
        LobbyDiscovery(LobbyInfo&);
        void updatePackets();
        void sendPackets();
        void receivePackets();

        void getGameInfo();


   
};
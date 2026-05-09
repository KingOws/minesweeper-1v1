#pragma once
#include "lobby.h"

class LobbyHosting : public Lobby{
    private:
        sf::SocketSelector selector;
        sf::TcpListener listener;
        std::vector<std::unique_ptr<sf::TcpSocket>> clientList;
    public:
        LobbyHosting();
        ~LobbyHosting();
        void runServer();

        void virtual sendPackets();
        void virtual receivePackets();
};
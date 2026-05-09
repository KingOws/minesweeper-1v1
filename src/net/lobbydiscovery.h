#pragma once
#include "lobby.h"

class LobbyDiscovery : public Lobby{
    private:

    public:
        LobbyDiscovery();
        ~LobbyDiscovery();
        void findServer();

        void virtual sendPackets();
        void virtual receivePackets();
};
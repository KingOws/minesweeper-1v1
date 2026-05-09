#pragma once
#include "lobby.h"

class LobbyDiscovery : public Lobby{
    private:
    public:
        LobbyDiscovery();
        ~LobbyDiscovery();
        void virtual establishConnection();

        //void findServer();
        // void virtual sendPackets();
        // void virtual receivePackets();
};
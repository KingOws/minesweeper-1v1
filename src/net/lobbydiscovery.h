#pragma once
#include "lobby.h"

class LobbyDiscovery : public Lobby{
    private:
    public:
        LobbyDiscovery();
        ~LobbyDiscovery();
        void virtual establishConnection(std::atomic<bool>&  running);

        void findServer();
        void const sendPackets() override;
        void const receivePackets() override;
        void const updatePackets() override;
};
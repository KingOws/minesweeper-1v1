#pragma once
#include "lobby.h"

class LobbyDiscovery : public Lobby{
    private:
    public:
        LobbyDiscovery();
        ~LobbyDiscovery();
        void virtual establishConnection(std::atomic<bool>&  running);

        void findServer();
        void sendPackets() override;
        void receivePackets() override;
        void updatePackets() override;
};
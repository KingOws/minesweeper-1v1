#pragma once
#include "lobby.h"

class LobbyDiscovery : public Lobby{
    private:
    public:
        LobbyDiscovery();
        ~LobbyDiscovery();
        void virtual establishConnection(std::atomic<bool>&  running);

        void findServer();
        // void virtual sendPackets() override;
        // void virtual receivePackets() override;
        // virtual void updatePackets() override;
};
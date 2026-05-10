#pragma once
#include "lobby.h"

struct PlayerAction{
    int playerId;

    //receive updates that the scene will draw later
    sf::Vector2f clickPos;
    bool isRightClick;
};

class LobbyDiscovery : public Lobby{
    private:
        PlayerAction playerAction;
    public:
        LobbyDiscovery();
        ~LobbyDiscovery();
        void virtual establishConnection(std::atomic<bool>&  running);

        void findServer();
        void sendPackets() override;
        void receivePackets() override;
        void updatePackets() override;
        PlayerAction& getPlayerAction() {return playerAction;};
};
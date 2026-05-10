#pragma once
#include "lobby.h"

class LobbyHosting : public Lobby{
    private:
        sf::SocketSelector selector;
        sf::TcpListener listener;
        LobbyInfo lobbyInfo;
        PlayerInfo mePlayer;
        std::vector<PlayerInfo> players;
        sf::Clock broadcastTimer;
    public:
        LobbyHosting();
        ~LobbyHosting();
        virtual void establishConnection(std::atomic<bool>&  running);
        void shutdown();

        void runServer();
        virtual void sendPackets() override;
        virtual void receivePackets() override;
        virtual void handlePlayerPackets(PlayerInfo&);
        LobbyInfo& getGameInfo(){return lobbyInfo;};
        PlayerInfo& getPlayerInfo(){return mePlayer;};
};
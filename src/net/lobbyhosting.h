#pragma once
#include "lobby.h"


struct PlayerInfo{
    std::unique_ptr<sf::TcpSocket> socket;

    int playerId;
    bool won = false;
    bool lost = false;

    //updated by host and then send updates to player
    Board board;
};

struct GameUpdate{
    int playerId;
    bool won;
    bool lost;

    sf::Vector2i tilePos;
    int tileValue;
};

class LobbyHosting : public Lobby{
    private:
        sf::SocketSelector selector;
        sf::TcpListener listener;
        LobbyInfo lobbyInfo;
        std::vector<PlayerInfo> players;
        sf::Clock broadcastTimer;
    public:
        LobbyHosting();
        ~LobbyHosting();
        virtual void establishConnection(std::atomic<bool>&  running);
        void shutdown();

        void runServer();
        virtual const void sendPackets() override;
        virtual const void receivePackets() override;
        virtual const void handlePlayerPackets(PlayerInfo&);
};
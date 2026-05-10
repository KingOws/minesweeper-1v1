#pragma once
#include "lobby.h"




struct LobbyInfo{
    int currentPlayers = 1;
    int maxPlayers = 2;
    bool inGame = false;
};

struct GameUpdate{
    int playerId;
    bool won;
    bool lost;

    sf::Vector2i tilePos;
    int tileValue;
};

struct PlayerInfo{
    std::unique_ptr<sf::TcpSocket> socket;

    int playerId;
    bool won = false;
    bool lost = false;

    //updated by host and then send updates to player
    Board board;
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
        virtual void sendPackets() override;
        virtual void receivePackets() override;
        virtual void handlePlayerPackets(PlayerInfo&);
};
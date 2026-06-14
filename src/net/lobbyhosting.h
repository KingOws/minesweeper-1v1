#pragma once
#include "lobby.h"
#include "../scenes/gameScene.h"
#include <memory>

struct PlayerInfo{
    std::unique_ptr<sf::TcpSocket> socket;
    std::optional<PlayerAction> playerAction;
    std::optional<GameUpdate> gameUpdate;
    std::optional<Board> board;

    PlayerInfo(std::unique_ptr<sf::TcpSocket> s) : socket(std::move(s)), playerAction() {}
    PlayerInfo(std::unique_ptr<sf::TcpSocket> s, int i) : socket(std::move(s)), playerAction(i) {}
};


class LobbyHosting : public Lobby{
    private:
        sf::SocketSelector selector;
        sf::TcpListener listener;
        sf::Clock broadcastTimer;

        GameScene* gScene;
        std::vector<std::optional<PlayerInfo>> players;

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

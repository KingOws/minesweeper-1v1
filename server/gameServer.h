#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Network.hpp>
#include "pactor.h"
#include "game.h"
#include "lobbyInfo.h"

class GameServer{
    private:
    sf::TcpListener listener;
    std::vector<std::unique_ptr<Game>> games;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<sf::TcpSocket>> pendingSockets;
    sf::SocketSelector selector;
    sf::Packet currentPacket;
    int PORT;
    bool on;

    public:
    GameServer();
    GameServer(int);
    ~GameServer();

    void acceptConnections();
    void authenticatePlayers();
    void receivePackets();
    void handlePackets(Player&);
    void sendPackets();
    Game* getGame(int);

    void createGame();
    void pruneStaleGame(const Player& currPlayer);
    inline const bool isOn(){return on;};
    inline sf::SocketSelector& getSelector(){return selector;};

    pactor<int> gamesToInt(std::vector<std::unique_ptr<Game>>& g){
        pactor<int> pacInt;
        for(const auto& gamePtr : g){
            if(gamePtr){
                pacInt.push_back(gamePtr->getId());
            }
        }
        return pacInt;
    }

    friend std::ostream& operator<<(std::ostream& os, GameServer& server){
        for(const auto& playerPtr : server.players){
            std::cout << playerPtr->playerId;
        }
        return os;
    }
};
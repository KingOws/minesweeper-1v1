#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "IScene.h"
#include "board.h"
#include "vec.h"


enum GameState{
    LOBBY,
    INGAME
};

struct GameUpdate{
    bool won;
    bool lost;

    sf::Vector2i tilePos;
    int tileValue;

    friend sf::Packet& operator>>(sf::Packet& p, GameUpdate& gu) {
        return p >> gu.won >> gu.lost >> gu.tilePos >> gu.tileValue;
    }

    friend sf::Packet& operator<<(sf::Packet& p, const GameUpdate& gu) {
        return p << gu.won << gu.lost << gu.tilePos << gu.tileValue;
    }
};

struct LobbyInfo{
    int currentPlayers = 1;
    int maxPlayers = 2;
    bool inGame = false;
    int difficulty;

    // SFML Packet Serialization
    friend sf::Packet& operator<<(sf::Packet& p, const LobbyInfo& l) {
        return p << l.currentPlayers << l.maxPlayers << l.inGame << l.difficulty;
    }

    friend sf::Packet& operator>>(sf::Packet& p, LobbyInfo& l) {
        return p >> l.currentPlayers >> l.maxPlayers >> l.inGame >> l.difficulty;
    }

};

struct PlayerAction{
    static int idGen; 
    int playerId;
    bool inGame;

    //receive updates that the scene will draw later
    sf::Vector2f clickPos;
    bool isRightClick;

    friend sf::Packet& operator<<(sf::Packet& p, const PlayerAction& pa) {
        return p << pa.clickPos << pa.isRightClick;
    }

    friend sf::Packet& operator>>(sf::Packet& p, PlayerAction& pa) {
        return p >> pa.playerId >> pa.inGame;
    }
    PlayerAction(){idGen++; playerId = idGen; inGame = false;};
    PlayerAction(int i){idGen++; playerId = i; inGame = false;};
};

class Lobby {
    protected:
        unsigned short GAME_PORT = 55001;
        std::unique_ptr<sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();

        unsigned short DiscoveryPort = 49152;
        sf::UdpSocket udpListener;
        mutable sf::Packet packet;
        sf::IpAddress playerAddress{192,168,0,0};
        sf::IpAddress remoteAddress{192,168,0,255};

        LobbyInfo lobbyInfo;
        PlayerAction playerAction;
        GameUpdate gameUpdate;

        bool hosting;
        bool connected;
        bool tcpLinkReady;

    public:
        Lobby();
        ~Lobby();

        bool isPlayerIPEmpty() {if (playerAddress == sf::IpAddress{192,168,0,0}) return true; return false;};
        
        virtual void establishConnection(std::atomic<bool>&  running) {};
        virtual void disconnect();

        virtual void updatePackets() {};
        virtual void sendPackets() {};
        virtual void receivePackets() {};

        virtual bool isConnected() const {return connected;};
        virtual const LobbyInfo& readLobbyInfo() const {return lobbyInfo;};
        virtual const PlayerAction& readPlayerAction() const {return playerAction;};

        virtual LobbyInfo& writeLobbyInfo() {return lobbyInfo;};
        virtual PlayerAction& writePlayerAction() {return playerAction;};
};
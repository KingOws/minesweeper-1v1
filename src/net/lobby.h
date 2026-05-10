#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include "IScene.h"
#include "board.h"


struct LobbyInfo{
    int currentPlayers = 1;
    int maxPlayers = 2;
    bool inGame = false;
    bool hosting = false;

    // SFML Packet Serialization
    friend sf::Packet& operator<<(sf::Packet& p, const LobbyInfo& l) {
        return p << l.currentPlayers << l.maxPlayers << l.inGame << l.hosting;
    }

    friend sf::Packet& operator>>(sf::Packet& p, LobbyInfo& l) {
        return p >> l.currentPlayers >> l.maxPlayers >> l.inGame >> l.hosting;
    }

    // Console Debug Output
    friend std::ostream& operator<<(std::ostream& os, const LobbyInfo& l) {
        os << "Lobby Status: " 
           << (l.hosting ? "[Hosting] " : "[Client] ")
           << (l.inGame ? "(In-Game) " : "(In-Lobby) ")
           << "Players: " << l.currentPlayers << "/" << l.maxPlayers;
        return os;
    }
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

struct PlayerAction{
    int playerId;
    bool inGame;

    //receive updates that the scene will draw later
    sf::Vector2f clickPos;
    bool isRightClick;
};

class Lobby {
    protected:
        unsigned short GAME_PORT = 55001;
        std::unique_ptr<sf::TcpSocket> socket = std::make_unique<sf::TcpSocket>();

        unsigned short DiscoveryPort = 49152;
        sf::UdpSocket udpListener;
        LobbyInfo l;
        PlayerInfo pi;
        PlayerAction pa;
        sf::Packet packet;
        sf::IpAddress playerAddress{192,168,0,0};
        sf::IpAddress remoteAddress{192,168,0,255};
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
        virtual LobbyInfo& getGameInfo(){return l;};
        virtual PlayerInfo& getPlayerInfo(){return pi;};
        virtual PlayerAction& getPlayerAction(){return pa;};
};
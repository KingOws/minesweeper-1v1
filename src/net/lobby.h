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
        mutable sf::Packet packet;
        sf::IpAddress playerAddress{192,168,0,0};
        sf::IpAddress remoteAddress{192,168,0,255};

        LobbyInfo lobbyInfo;
        PlayerAction playerAction;

        bool hosting;
        bool connected;
        bool tcpLinkReady;

    public:
        Lobby();
        ~Lobby();

        bool isPlayerIPEmpty() {if (playerAddress == sf::IpAddress{192,168,0,0}) return true; return false;};
        
        virtual void establishConnection(std::atomic<bool>&  running) {};
        virtual void disconnect();

        virtual const void updatePackets() {};
        virtual const void sendPackets() {};
        virtual const void receivePackets() {};

        virtual bool isConnected() const {return connected;};
        virtual const LobbyInfo& readLobbyInfo() const {return lobbyInfo;};
        virtual const PlayerAction& readPlayerAction() const {return playerAction;};

        virtual LobbyInfo& writeLobbyInfo() {return lobbyInfo;};
        virtual PlayerAction& writePlayerAction() {return playerAction;};
};
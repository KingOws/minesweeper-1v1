#pragma once
#include <vector>
#include <iostream>
#include <SFML/network.hpp>
#include "lobbyInfo.h"

class Player{
    public:
        static int idGen;
        int playerId;
        std::unique_ptr<sf::TcpSocket> socket;
        LobbyInfo info;
        bool isAuth;


        Player();
        Player(std::unique_ptr<sf::TcpSocket>, LobbyInfo&, bool);
        ~Player();
        void printInfo(){};
        inline int getId() {return playerId;};

};
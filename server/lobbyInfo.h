#pragma once
#include "pactor.h"

struct LobbyInfo{
    bool hosting;
    bool inGame;
    bool gameCreated;
    int lobbyId;
    int playerId;
    int currentPlayers;
    int maxPlayers;
    pactor<int> availableGames;

    friend sf::Packet& operator<<(sf::Packet& p, LobbyInfo& l){
       p << l.hosting << l.inGame << l.gameCreated << l.lobbyId << l.playerId << l.currentPlayers << l.maxPlayers << l.availableGames;
        return p;
    }

    friend sf::Packet& operator>>(sf::Packet& p, LobbyInfo& l){

        p >> l.hosting >> l.inGame >> l.gameCreated >> l.lobbyId >> l.playerId >> l.currentPlayers >> l.maxPlayers >> l.availableGames;
        return p;

    }
};
#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "player.h"

class Game{
    private:
        static int idGen;
        int gameId;
        std::vector<Player*> players;
        int maxPlayers;

    public:
        Game();
        ~Game();
        int getId(){return gameId;};
        inline void addPlayer(Player* p) {players.push_back(p);};
        inline int getNumPlayers(){return players.size();};
        inline int getMaxPlayers(){return maxPlayers;};
        inline std::vector<Player*>& getPlayers(){return players;};
};
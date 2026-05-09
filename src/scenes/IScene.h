#pragma once
#include <SFML/Graphics.hpp>
#include "pactor.h"
#include <iostream>
class SceneManager;

enum class SceneAction{None, goToMainMenu, startGame, goToNetworking, goToMenu, startLobby, searchLobby, goBack, Exit};
enum class Difficulty {easy, medium, hard};
enum class PlayerMode {single, multi};
enum class NetworkingMode {hosting, joining};

struct LobbyInfo{
    bool hosting = false;
    bool inGame = false;
    bool gameCreated = false;
    int playerId = -1;
    int currentPlayers = 0;
    int maxPlayers = 2;
    pactor<int> availableGames = pactor<int>{}; 

    friend sf::Packet& operator<<(sf::Packet& p, LobbyInfo& l){
        p << l.hosting << l.inGame << l.gameCreated << l.playerId << l.currentPlayers << l.maxPlayers << l.availableGames;
        return p;
    }

    friend sf::Packet& operator>>(sf::Packet& p, LobbyInfo& l){
        p >> l.hosting >> l.inGame >> l.gameCreated >> l.playerId >> l.currentPlayers >> l.maxPlayers >> l.availableGames;
        return p;
    }

    friend std::ostream& operator<<(std::ostream& p, LobbyInfo& l){
        p << "Hosting: " << l.hosting << " In Game: " << l.inGame << " Game created: " << l.gameCreated  << " Player Id: " << l.playerId << " Current Players: " << l.currentPlayers << " Max Players: " << l.maxPlayers << " \nAvailable Games:\n " << l.availableGames;
        return p;
    }

};

class IScene{
    private:
    public:
        IScene() {
            if (!font.openFromFile("../fonts/arial.ttf"))
                std::cerr << "Error: could not load font" << std::endl;
        };
        virtual ~IScene() = default;
        virtual void draw(sf::RenderWindow &window) =0;
        virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos) = 0;
        virtual SceneAction handleRightEvent(sf::Vector2f &mousePos) = 0;
        virtual SceneAction handleEsc(){
            return SceneAction::goBack;
        }
        virtual void update() = 0;
        sf::Font font;
};
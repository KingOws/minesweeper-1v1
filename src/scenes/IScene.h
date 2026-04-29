#pragma once
#include <SFML/Graphics.hpp>
#include "pactor.h"
class SceneManager;

enum class SceneAction{None, goToMainMenu, startGame, goToNetworking, goToMenu, startLobby, searchLobby, goBack, Exit};
enum class Difficulty {easy, medium, hard};
enum class PlayerMode {single, multi};
enum class NetworkingMode {hosting, joining};

struct LobbyInfo{
    bool hosting = false;
    bool gameCreated = false;
    int lobbyId = 0;
    int currentPlayers = 0;
    int maxPlayers = 2;
    pactor<int> availableGames; 
};

class IScene{
    private:
    public:
        IScene() {};
        virtual ~IScene() = default;
        virtual void draw(sf::RenderWindow &window) =0;
        virtual SceneAction handleLeftEvent(sf::Vector2f &mousePos) = 0;
        virtual SceneAction handleRightEvent(sf::Vector2f &mousePos) = 0;
        virtual SceneAction handleEsc(){
            return SceneAction::goBack;
        }
        virtual void update() = 0;
};
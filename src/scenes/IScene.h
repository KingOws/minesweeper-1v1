#pragma once

#include <SFML/Graphics.hpp>

class SceneManager;

enum class SceneAction{None, goToMainMenu, startGame, goToNetworking, goToMenu, startLobby, searchLobby, goBack, Exit};
enum class Difficulty {easy, medium, hard};
enum class PlayerMode {single, multi};
enum class NetworkingMode {hosting, joining};

struct GameInfo{
    bool hosting = false;
    bool gameCreated = false;
    int playerCount = 0;
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
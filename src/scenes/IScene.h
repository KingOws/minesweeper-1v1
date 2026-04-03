#pragma once

#include <SFML/Graphics.hpp>

class SceneManager;

enum class SceneAction{None, startGame, goToNetworking, goToMenu, startLobby, searchLobby, Exit};
enum class Difficulty {easy, medium, hard};
enum class PlayerMode {single, multi};
enum class NetworkingMode {hosting, joining};

class IScene{
    private:
    public:
        IScene() {};
        virtual ~IScene() = default;
        virtual void draw(sf::RenderWindow &window) =0;
        virtual SceneAction handleEvent(sf::Vector2f &mousePos) = 0;
        virtual void update() = 0;
};
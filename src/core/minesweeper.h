#pragma once
#include "SceneManager.h"
#include "spritemanager.h"
#include "networkManager.h"

//SFML
#include <SFML/Graphics.hpp>

//std
#include <variant>


enum class GAMESTATE {
    MENU, 
    LOBBY,

    HOSTING_WAITING,
    HOSTING_DIFF_SELECT,
    HOSTING_PLAYING, 

    JOINING_WAITING,
    JOINING_PLAYING,
    
    SP_DIFF_SELECT,
    SP_PLAYING
};

struct NetworkInfo{

};

inline constexpr bool isMultiplayer(GAMESTATE state) {
    return (state >= GAMESTATE::HOSTING_WAITING && state <= GAMESTATE::JOINING_PLAYING);
}

class Minesweeper{
    public:
        Minesweeper();
        void initWindow();

        void run();
        void handleEvents();
        void display(); 

        void update();
        void updateScManager();
        bool updateNetManager();
        void createNetManager();

        bool isRunning(){return m_isRunning;}

    private:
        SceneManager sceneManager;
        std::unique_ptr<NetworkManager> networkManager;

        GAMESTATE gameState;
        NetworkInfo networkInfo;

        sf::RenderWindow window{sf::VideoMode({800, 600}), "Minesweeper Client"};

        sf::Image icon;
        bool m_isRunning;
};
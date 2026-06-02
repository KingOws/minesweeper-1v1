#pragma once
#include "SceneManager.h"
#include "spritemanager.h"
#include "networkManager.h"
#include <SFML/Graphics.hpp>


class Minesweeper{
    public:
        Minesweeper();
        void initWindow();

        void run();
        auto getEvents();
        void display(); 

        void updateScManager();
        void updateNetManager();
        void updateSpriteManager();

        bool isRunning(){return m_isRunning;}

    private:
        SceneManager sceneManager;
        NetworkManager networkManager;
        SpriteManager spriteManager;
        sf::RenderWindow window{sf::VideoMode({800, 600}), "Minesweeper Client"};

        sf::Image icon;
        bool m_isRunning;
};
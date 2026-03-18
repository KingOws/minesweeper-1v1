#pragma once
#include <optional>
#include <SFML/Graphics.hpp>
#include "menu.h"

class Menu;  // Forward declare Menu

class Player{
    private:

    public:
    Player();
    void leftClick(sf::RenderWindow&, Menu&, const sf::Event&);
    void rightClick(sf::RenderWindow&, Menu&, const sf::Event&);
};
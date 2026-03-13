#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

class Menu;

class Player{
    private:

    public:
    Player();
    void leftClick(sf::RenderWindow&, Menu&, const std::optional<sf::Event>&);
    void rightClick(sf::RenderWindow&, Menu&, const std::optional<sf::Event>&);
};
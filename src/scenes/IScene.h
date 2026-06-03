#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum SceneAction; 

class IScene{
    private:
    public:
        sf::Font font;
        IScene() {
            if (!font.openFromFile("../fonts/arial.ttf"))
                std::cerr << "Error: could not load font" << std::endl;
        };
        virtual ~IScene() = default;
        virtual void draw(sf::RenderWindow &window) =0;
        virtual SceneAction handleEvent(sf::Event& e) = 0;
        virtual void update() = 0;
};
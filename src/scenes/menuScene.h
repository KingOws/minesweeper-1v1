#pragma once

#include <IScene.h>
#include <SFML/Graphics.hpp>

class SceneManager;

class MenuScene: public IScene{
    private:
    sf::RectangleShape boxes[3];
    sf::Font font;
    sf::Text textFields[3];
    Difficulty difficulty;

    public:
    MenuScene();
    ~MenuScene();
    virtual void draw(sf::RenderWindow &window); 
    virtual void update() {return;};
    virtual SceneAction handleEvent(sf::Vector2f &mousePos);
    inline Difficulty getDiff(){return difficulty;};
};
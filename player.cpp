#include "player.h"
#include "menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

Player::Player(){
    
}

void Player::leftClick(sf::RenderWindow& window, Menu& menu, const sf::Event& event){
    if(event.is<sf::Event::MouseButtonPressed>()){
        auto mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if(mouseEvent->button == sf::Mouse::Button::Left){
            sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
            if(!menu.isBoard()){
                std::string difficulty = menu.handleClick(mousePos);
                if(difficulty == "easy"){menu.createBoard(9,9,10);}
                if(difficulty == "medium"){menu.createBoard(16,16,40);}
                if(difficulty == "hard"){menu.createBoard(16,30,99);}
            }
        }
    }
}

void Player::rightClick(sf::RenderWindow& window, Menu& menu, const sf::Event& event){
    if(event.is<sf::Event::MouseButtonPressed>()){
        auto mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if(mouseEvent->button == sf::Mouse::Button::Right){
            sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
            if(menu.isBoard()){

            }
        }
    }
}

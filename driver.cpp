#include <SFML/Graphics.hpp>
#include "menu.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper Client");
    Menu m;

    while (window.isOpen()){
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if(event->is<sf::Event::MouseButtonPressed>()){
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

                if(mouseEvent->button == sf::Mouse::Button::Left){
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
                    std::string difficulty = m.handleClick(mousePos);

                    if(difficulty == "easy")
                        m.createBoard(9,9,10);
                    if(difficulty == "medium")
                        m.createBoard(16,16,40);
                    if(difficulty == "hard")
                        m.createBoard(16,30,99);
                }
            }
        }

        window.clear({225,255,225,225});
        m.drawMenu(window);
        window.display();
    }
    return 0;
}
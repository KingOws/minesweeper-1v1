#include <SFML/Graphics.hpp>
#include "SceneManager.h"

int main()
{   
    sf::Image icon;
    if (!icon.loadFromFile("../src/images/icon.png")) {
        std::cerr << "Failed to load icon.png" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper Client");
    window.setIcon(icon);
    SceneManager sm;

    while (window.isOpen()){
        while (auto event = window.pollEvent()){
            const sf::Event& e = *event;
            if (event->is<sf::Event::Closed>()){
                window.close();
            }

            if(event->is<sf::Event::MouseButtonPressed>()){
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if(mouseEvent->button == sf::Mouse::Button::Left){
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
                    sm.processAction(sm.getScene()->handleEvent(mousePos));
                }
            }
        }
        window.clear({225,255,225,225});
        sm.getScene()->update();
        sm.getScene()->draw(window);
        window.display();
    }
    return 0;
}

    
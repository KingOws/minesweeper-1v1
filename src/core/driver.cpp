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

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::A) {
                    // A was pressed — trigger your autocomplete here
                    if(GameScene* g = dynamic_cast<GameScene*>(sm.getScene())){
                        g->handleDevWin();
                    }
                }
            }
            if(event->is<sf::Event::MouseButtonPressed>()){
                const sf::Event::MouseButtonPressed* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if(mouseEvent->button == sf::Mouse::Button::Left){
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
                    sm.processAction(sm.getScene()->handleLeftEvent(mousePos));
                }
                if(mouseEvent->button == sf::Mouse::Button::Right){
                    sf::Vector2f mousePos = window.mapPixelToCoords({mouseEvent->position.x, mouseEvent->position.y});
                    sm.processAction(sm.getScene()->handleRightEvent(mousePos));
                }
            }
        }

        sm.updateAndSwap();

        window.clear({255, 255, 255, 255});
        sm.displayScene(window);
        window.display();
    }
    return 0;
}

    
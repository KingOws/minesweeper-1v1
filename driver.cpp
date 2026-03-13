#include <SFML/Graphics.hpp>
#include "menu.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper Client");
    Menu m;
    m.createPlayer();

    while (window.isOpen()){
        while (auto event = window.pollEvent()){
            const sf::Event& e = *event;
            if (event->is<sf::Event::Closed>())
                window.close();
            m.getPlayer().leftClick(window, m, e);
            m.getPlayer().rightClick(window, m, e);
        }
    window.clear({225,255,225,225});
    m.drawMenu(window);
    window.display();
    }
    return 0;
}
    
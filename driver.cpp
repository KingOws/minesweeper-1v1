#include <SFML/Graphics.hpp>
#include "menu.h"

int main()
{   
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper Client");
    Menu m;
    m.createPlayer();

    while (window.isOpen()){
        while (auto event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
            m.getPlayer().leftClick(window, m, event);
            m.getPlayer().rightClick(window, m, event);
        }
    window.clear({225,255,225,225});
    m.drawMenu(window);
    window.display();
    }
    return 0;
}
    
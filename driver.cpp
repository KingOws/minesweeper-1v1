#include <SFML/Graphics.hpp>
#include "menu.h"

int main()
{   
    sf::Image icon;
    if (!icon.loadFromFile("../images/icon.png")) {
        std::cerr << "Failed to load icon.png" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minesweeper Client");
    window.setIcon(icon);
    Menu m;
    m.createPlayer();

    while (window.isOpen()){
        while (auto event = window.pollEvent()){
            const sf::Event& e = *event;
            if (event->is<sf::Event::Closed>())
                window.close();
            m.getPlayer()->leftClick(window, m, e);
            m.getPlayer()->rightClick(window, m, e);
        }
    window.clear({225,255,225,225});
    m.drawMenu(window);
    window.display();
    if(m.isBoard()){m.checkGameWon();}
    }
    return 0;
}
    